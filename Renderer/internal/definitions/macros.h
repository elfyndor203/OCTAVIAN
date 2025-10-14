#pragma once
#include "standards/myStandards.h"
#include "renderer/rendererObject/rendererObject.h"

#define NEW_GLOBJECT(inputDataArray, inputDataCount) ((GLRequest){.ID = -1, .dataArray = inputDataArray, .dataCount = inputDataCount, .createNewID = true})				// for simpler use of GLRequest, -1 == create new
#define EXISTING_GLOBJECT(IDNum) ((GLRequest){.ID = (IDNum), .createNewID = false})
#define NEW_VAO NEW_GLOBJECT(0, 0)	// aliases
#define NEW_VBO(dataArray, dataCount) NEW_GLOBJECT(dataArray, dataCount)
#define NEW_EBO(dataArray, dataCount) NEW_GLOBJECT(dataArray, dataCount)
#define NO_EBO EXISTING_GLOBJECT(0)											// when no EBO, createNEWID is false, but nothing will get bound
#define EXISTING_VAO(IDNum) EXISTING_GLOBJECT(IDNum)
#define EXISTING_VBO(IDNum) EXISTING_GLOBJECT(IDNum)
#define EXISTING_EBO(IDNum) EXISTING_GLOBJECT(IDNum)