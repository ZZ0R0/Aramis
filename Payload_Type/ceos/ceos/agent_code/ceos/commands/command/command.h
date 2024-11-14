#pragma once

#include <string>
#include <windows.h>
#include "Package.h"
#include "Parser.h"
#include <cstdio>

bool executeCommand(std::string cmd, std::string currentDirectory, std::string& output);