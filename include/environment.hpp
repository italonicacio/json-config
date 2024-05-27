#pragma once
#include <string>

class EnvironmentVariables {
public:

	std::string runtime_mode;
	std::string path;
	int size;
	int max_size;
	float epsilon;
};

class Environment : public EnvironmentVariables {
protected:

	Environment();
	~Environment();

	static Environment* _instance;

	class Deleter {
	public:
		~Deleter() {
			if(_instance != nullptr) {
				delete _instance;
			}
		}
	};

	static Deleter _deleter;

public:

	Environment(Environment const&) = delete;
	void operator=(Environment const&) = delete;

	static Environment* GetInstance();
	void Load();
	void Load(std::istream& is);
	void Validate();
};

