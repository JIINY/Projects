#include "AddressBook.hpp"
#include <vector>
#include <utility>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <cstdio>
#include "../Common/ResultEnums.hpp"
#include "Personal.hpp"
using namespace std;


SaveOperationResult AddressBook::saveFile(const string& filename) const 
{
	ofstream outFile(filename, std::ios::binary);

	if (!outFile) //쓰기 가능한지(e.g. 폴더 권한 문제)
	{ 
		return SaveOperationResult::FAIL;
	}

	outFile << "\xEF\xBB\xBF"; //UTF-8 BOM 표기
	outFile << "Name,Phone,Address,ZipCode,Email\n"; //CSV 헤더

	for (const auto& p : personal_) 
	{
		outFile << p.getName() << ',' 
			<< p.getPhone() << ',' 
			<< p.getAddress() << ',' 
			<< p.getZipCode() << ',' 
			<< p.getEmail() << '\n';
	}
	return SaveOperationResult::SUCCESS;
}

LoadOperationResult AddressBook::loadFile(const string& filename) 
{
	ifstream inFile(filename);

	if (!inFile) 
	{
		if (!filesystem::exists(filename)) 
		{
			return LoadOperationResult::NOT_EXIST_FILE;
		}
		return LoadOperationResult::FAIL;
	}

	//UTF-8 BOM (3-byte) 건너뛰기
	char bom[3] = { 0 };
	inFile.read(bom, 3);
	if (static_cast<unsigned char>(bom[0]) != 0xEF ||
		static_cast<unsigned char>(bom[1]) != 0xBB ||
		static_cast<unsigned char>(bom[2]) != 0xBF)
	{
		inFile.seekg(0, std::ios::beg);
	}

	personal_.clear();
	string line;

	//CSV 헤더 한 줄 건너뛰기
	if (!getline(inFile, line)) 
	{
		return LoadOperationResult::EMPTY_FILE;
	}

	//읽기 시작
	while (getline(inFile, line)) 
	{
		istringstream data(line);
		PersonalData input;
		getline(data, input.name, ',');
		getline(data, input.phone, ',');
		getline(data, input.address, ',');
		getline(data, input.zipCode, ',');
		getline(data, input.email, ',');

		Personal p(input);
		personal_.push_back(p);
	}
	return LoadOperationResult::SUCCESS;
}


AddOperationResult AddressBook::add(const PersonalData& p) 
{ 
	return processAdd(p);
}

vector<pair<PersonalData, int>> AddressBook::searchByName(const string& query) const 
{
	vector<pair<PersonalData, int>> results;
	for (int i = 0; i < personal_.size(); ++i) 
	{
		const string& name = personal_[i].getName();
		if (query.empty() && name.empty() || !query.empty() && name.find(query) != string::npos) 
		{
			results.push_back({ personal_[i].getData(), i });
		}
	}
	return results;
}

vector<pair<PersonalData, int>> AddressBook::searchByPhone(const string& query) const
{
	vector<pair<PersonalData, int>> results;
	for (int i = 0; i < personal_.size(); ++i)
	{
		const string& phone = personal_[i].getPhone();
		if (query.empty() && phone.empty() || !query.empty() && phone.find(query) != string::npos)
		{
			results.push_back({ personal_[i].getData(), i });
		}
	}
	return results;
}

vector<pair<PersonalData, int>> AddressBook::searchByAddress(const string& query) const
{
	vector<pair<PersonalData, int>> results;
	for (int i = 0; i < personal_.size(); ++i)
	{
		const string& address = personal_[i].getAddress();
		if (query.empty() && address.empty() || !query.empty() && address.find(query) != string::npos)
		{
			results.push_back({ personal_[i].getData(), i });
		}
	}
	return results;
}

vector<pair<PersonalData, int>> AddressBook::searchByZipCode(const string& query) const
{
	vector<pair<PersonalData, int>> results;
	for (int i = 0; i < personal_.size(); ++i)
	{
		const string& zipCode = personal_[i].getZipCode();
		if (query.empty() && zipCode.empty() || !query.empty() && zipCode.find(query) != string::npos)
		{
			results.push_back({ personal_[i].getData(), i });
		}
	}
	return results;
}

vector<pair<PersonalData, int>> AddressBook::searchByEmail(const string& query) const
{
	vector<pair<PersonalData, int>> results;
	for (int i = 0; i < personal_.size(); ++i)
	{
		const string& email = personal_[i].getEmail();
		if (query.empty() && email.empty() || !query.empty() && email.find(query) != string::npos)
		{
			results.push_back({ personal_[i].getData(), i });
		}
	}
	return results;
}


AddOperationResult AddressBook::processAdd(const PersonalData& p) 
{
	Personal data;
	AddOperationResult result = data.setData(p);

	if (result != AddOperationResult::SUCCESS) { return result; }

	auto pos = lower_bound(personal_.begin(), personal_.end(), data,
		[](const Personal& a, const Personal& b) 
		{
			return a.getName() < b.getName();
		});
	lastAdd_ = static_cast<int>(pos - personal_.begin());
	this->personal_.insert(pos, data);
	return AddOperationResult::SUCCESS;
}

AddOperationResult AddressBook::edit(int originalIndex, const PersonalData& newData) 
{
	Personal p;
	AddOperationResult validationResult = p.setData(newData);
	if (validationResult != AddOperationResult::SUCCESS) 
	{ 
		return validationResult; 
	}

	//newData가 유효하다면 기존 데이터를 삭제
	std::string removedName;
	RemoveOperationResult removeResult = processRemove(originalIndex, removedName);
	if (removeResult != RemoveOperationResult::SUCCESS) 
	{
		return AddOperationResult::FAIL;
	}

	//newData를 다시 추가
	AddOperationResult addResult = add(newData);
	
	return addResult;
}

RemoveOperationResult AddressBook::remove(int index, string& name) 
{
	RemoveOperationResult result = processRemove(index, name);
	return result;
}

RemoveOperationResult AddressBook::processRemove(int index, string& name) 
{
	int length = static_cast<int>(this->personal_.size());
	if (index < 0 || index >= length) { return RemoveOperationResult::WRONG_INDEX; }

	if (popPersonal(index, name)) 
	{
		length--;
		return RemoveOperationResult::SUCCESS;
	}
	return RemoveOperationResult::FAIL;
}

RemoveOperationResult AddressBook::removeAll(const string& filename)
{
	RemoveOperationResult result = processRemoveAll(filename);
	return result;
}

RemoveOperationResult AddressBook::processRemoveAll(const string& filename) 
{
	if (std::remove(filename.c_str()) != 0) //AddressBook::remove()가 있기 때문에, 어떤 remove인지를 명시
	{
		ifstream f(filename);
		if (f.good()) 
		{
			//파일이 존재하는데 삭제가 안된 경우(사용중 or 권한 없음)
			return RemoveOperationResult::FILE_DELETE_FAILED;
		}
	}

	personal_.clear();
	lastAdd_ = -1;

	std::remove(filename.c_str()); //삭제 성공시 0을 반환, 파일이 없어서 삭제를 못해도 목적 달성
	return RemoveOperationResult::SUCCESS;
}

bool AddressBook::popPersonal(int index, string& name) //마찬가지로 length가공 어떻게 할 건지 맞춰서 매개변수 수정할 것
{
	name = personal_[index].getName();
	personal_.erase(personal_.begin() + (index));
	return true;
}

int AddressBook::findIndexByData(const PersonalData& dataToFind) const 
{
	//같은 이름이 시작되는 위치 찾기
	auto it = lower_bound(personal_.begin(), personal_.end(), Personal(dataToFind), 
		[](const Personal& a, const Personal& b) {
			return a.getName() < b.getName();
		});

	while (it != personal_.end() && it->getName() == dataToFind.name) 
	{
		if (it->getData() == dataToFind) 
		{
			return static_cast<int>(it - personal_.begin());
		}
		++it;
	}

	return -1;
}

