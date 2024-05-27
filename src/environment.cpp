#include <fstream>
#include <json/json.h>
#include <filesystem>

#include "environment.hpp"
#include "utils/utils.hpp"

Environment* Environment::_instance = nullptr;

Environment::Environment() {
	Load();
	Validate();
}

void Environment::Load(std::istream& is) {
	Json::Value root;
	Json::CharReaderBuilder builder;
	std::string errs;

	bool ok = Json::parseFromStream(builder, is, &root, &errs);
	if(!ok) {
		return;
	}

	this->runtime_mode = root["runtime_mode"].asString();
	this->path = root["path"].asString();
	this->size = root["size"].asInt();
	this->max_size = root["max_size"].asInt();
	this->epsilon = root["epsilon"].asFloat();
}

void Environment::Load() {
	std::ifstream ifs("../config.json", std::ifstream::binary);
	Load(ifs);
}

void Environment::Validate() {
	const int32_t MAX_size = this->max_size;
	const int32_t MIN_size = 0;
	std::vector<std::string> runtime_modes = { "dev", "prod" };

	if(!Utils::contains(runtime_modes, this->runtime_mode)) {
		throw std::invalid_argument("Invalid runtime mode: " + this->runtime_mode);
	}

	if(!std::filesystem::exists(this->path)) {
		throw std::invalid_argument("Invalid path");
	}

	if(this->max_size < MIN_size) {
		throw std::invalid_argument("max size needs to be greater than min size: min size = " + std::to_string(MIN_size));
	}

	if(this->size > MAX_size && this->size < MIN_size) {
		throw std::invalid_argument("size must be a value between" + std::to_string(MIN_size) + " and " + std::to_string(MAX_size));
	}

}

Environment::~Environment() {
	delete _instance;
}

Environment* Environment::GetInstance() {
	if(_instance == nullptr) {
		_instance = new Environment();
	}
	return _instance;
}
