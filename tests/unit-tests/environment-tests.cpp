#include <gtest/gtest.h>

#include "environment.hpp"


TEST(EnvironmentTest, LoadAndValidate) {
	// Crie um JSON de teste em memória
	std::string json = R"({
        "runtime_mode": "dev",
        "path": ".",
        "size": 10,
        "max_size": 100,
        "epsilon": 0.1
    })";
	std::istringstream iss(json);

	// Carregue o ambiente a partir do JSON
	Environment* env = Environment::GetInstance();
	env->Load(iss);

	// Valide o ambiente
	EXPECT_NO_THROW(env->Validate());
}

TEST(EnvironmentTest, GetEpsilonWithSameValue) {
	// Crie um JSON de teste em memória
	std::string json = R"({
        "runtime_mode": "dev",
        "path": ".",
        "size": 10,
        "max_size": 100,
        "epsilon": 0.0000001
    })";
	std::istringstream iss(json);

	// Carregue o ambiente a partir do JSON
	Environment* env = Environment::GetInstance();
	env->Load(iss);
	env->Validate();

	EXPECT_NEAR(env->epsilon, static_cast<float>(0.0000001), 1e-1);
}

TEST(EnvironmentTest, PassingWrongRuntimeMode) {
	// Crie um JSON de teste em memória
	std::string json = R"({
        "runtime_mode": "error",
        "path": ".",
        "size": 10,
        "max_size": 100,
        "epsilon": 0.0000001
    })";
	std::istringstream iss(json);

	Environment* env = Environment::GetInstance();
	env->Load(iss);

	EXPECT_ANY_THROW(env->Validate());
}
