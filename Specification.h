#pragma once

#include "cocos2d.h"
#include <string>






namespace DEF_SETT {
	// Ratio
	const float cHalf = 0.5f;
	const float cOneThird = 1.0f / 3.0f;
	const float cTwoThird = 2.0f / 3.0f;
	const float cOneQuaters = 1.0f / 4.0f;
	const float cThreeQuaters = 3.0f / 4.0f;
	const float cOneSixth = 1.0f / 6.0f;
	const float cFullOpacity = 255.0f;
	const float cFullSize = 1.0f;
	const float cOnePixel = 1.0f;

	const int cVerticesAmount = 4;
}


// JsonCreator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"


using namespace rapidjson;

int main()
{

	Document doc;
	doc.SetObject();

	rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

	doc.AddMember("Font", "fonts/arial.ttf", allocator);
	doc.AddMember("ActionDuration", 2.0, allocator);
	doc.AddMember("FontSize", 18.0, allocator);
	doc.AddMember("BackGroundImageFile", "bg.png", allocator);
	doc.AddMember("Sprite1ImageFile", "sprite1.png", allocator);
	doc.AddMember("Sprite2ImageFile", "sprite2.png", allocator);
	doc.AddMember("Sprite3ImageFile", "sprite3.png", allocator);
	doc.AddMember("QuitBTNNormalImageFile", "quitIcon1.png", allocator);
	doc.AddMember("QuitBTNSelectedImageFile", "quitIcon2.png", allocator);
	doc.AddMember("BTNNormalImageFile", "plank1.png", allocator);
	doc.AddMember("BTNSelectedImageFile", "plank2.png", allocator);
	// doc.AddMember("BTN1InitModeText", "plank2.png", allocator);
	
	
	Value METALLIC_GOLD(kArrayType);
	METALLIC_GOLD.PushBack(212, allocator);
	METALLIC_GOLD.PushBack(175, allocator);
	METALLIC_GOLD.PushBack(55, allocator);

	doc.AddMember("METALLIC_GOLD", METALLIC_GOLD, allocator);

	Value VIOLET(kArrayType);
	VIOLET.PushBack(131, allocator);
	VIOLET.PushBack(55, allocator);
	VIOLET.PushBack(127, allocator);

	doc.AddMember("VIOLET", VIOLET, allocator);

	// Convert JSON document to string
	rapidjson::StringBuffer strbuf;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(strbuf);

	doc.Accept(writer);

	std::cout << strbuf.GetString() << std::endl;

	std::ofstream of("specifications.json");
	std::string json(strbuf.GetString());
	
	of << json;
	if (!of.good()) throw std::runtime_error("Can't write the JSON string to the file!");
	of.close();

	


	//Document doc;
	//doc.SetObject();

	//rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

	//size_t sz = allocator.Size();

	//doc.AddMember("version", "version", allocator);
	//doc.AddMember("testId", 2, allocator);
	//doc.AddMember("group", 3, allocator);
	//doc.AddMember("order", 4, allocator);

	//Value tests(kArrayType);
	//Value obj(kObjectType);
	//Value val(kObjectType);

	//obj.AddMember("id", 1, allocator);

	//std::string description = "a description";
	//val.SetString(description.c_str(), static_cast<SizeType>(description.length()), allocator);
	//obj.AddMember("description", val, allocator);

	//std::string help = "some help";
	//val.SetString(help.c_str(), static_cast<SizeType>(help.length()), allocator);
	//obj.AddMember("help", val, allocator);

	//std::string workgroup = "a workgroup";
	//val.SetString(workgroup.c_str(), static_cast<SizeType>(workgroup.length()), allocator);
	//obj.AddMember("workgroup", val, allocator);

	//val.SetBool(true);
	//obj.AddMember("online", val, allocator);

	//tests.PushBack(obj, allocator);
	//doc.AddMember("tests", tests, allocator);

	//// Convert JSON document to string
	//rapidjson::StringBuffer strbuf;
	//rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(strbuf);




	//doc.Accept(writer);

	//std::cout << strbuf.GetString() << std::endl;

	//std::ofstream of("example.json");
	//std::string json(strbuf.GetString());
	////std::string json(doc.GetString());
	//of << json;
	//if (!of.good()) throw std::runtime_error("Can't write the JSON string to the file!");
	//of.close();

	//std::ifstream in("example.json");

	//const char json[] = "{ \"hello\" : \"world\" }";

	//rapidjson::StringBuffer strbufIn;
	////in >> strbufIn;

    return 0;
}


