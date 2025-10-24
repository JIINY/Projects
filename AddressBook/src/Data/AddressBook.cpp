#include "AddressBook.hpp"
#include <vector>
#include <utility>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <filesystem>
#include "../Common/ResultEnums.hpp"
#include "Personal.hpp"
using namespace std;


SaveOperationResult AddressBook::saveFile(const string& filename) const 
{
	ofstream outFile(filename);

	if (!outFile) //쓰기 가능한지(e.g. 폴더 권한 문제)
	{ 
		return SaveOperationResult::FAIL;
	}

	for (const auto& p : personal_) 
	{
		outFile << p.getName() << ',' << p.getPhone() << ',' << p.getAddress() << ',' << p.getZipCode() << ',' << p.getEmail() << '\n';
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

	personal_.clear();
	string line;
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

bool AddressBook::popPersonal(int index, string& name) //마찬가지로 length가공 어떻게 할 건지 맞춰서 매개변수 수정할 것
{
	name = personal_[index].getName();
	personal_.erase(personal_.begin() + (index));
	return true;
}
