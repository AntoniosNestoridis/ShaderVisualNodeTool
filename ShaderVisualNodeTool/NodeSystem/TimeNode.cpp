#include "TimeNode.h"



TimeNode::TimeNode()
{
	auto graph = Graph::getInstance();
	Type = BaseNodeType::InputnodeUniform;
	//inputType = InputNodeType::ConstantVariable;
	//UniqueID = graph->AssignID();
	//HasCompiled = false;


	ValueType type = Float;
	//output struct creation
	Connection connect;
	connect.ConnectedNode = nullptr;
	connect.ConnectionIndex = -1;
	connect.VariableType = type;

	connect.Enabled = true;

	Name = "Time";
	connect.Name = "Timer";

	//Don't get it from graph
	connect.Value.f_var = graph->time;
	value.f_var = graph->time;
	
	Output.clear();
	Output.push_back(connect);

	//instantly add to uniform nodes list
	//graph->UniformNodes.push_back(shared_from_this());


}


TimeNode::~TimeNode()
{
	//remove from Uniform nodes
}

void TimeNode::EditUniform()
{

	
	//Program ID , this needs to be passed as a parameter maybe
	auto ManagerInstance = Graph::getInstance();
	Shader* program = ManagerInstance->daShader;
	
	std::string name = Output.at(0).Name;
	std::string slotName = std::to_string(this->UniqueID) + "->0";
	std::string uniqueOutName = ManagerInstance->AssignUniqueName(name, slotName);

	program->Use();

	unsigned int uloc = glGetUniformLocation(program->ID, uniqueOutName.c_str());

	//std::cout << ManagerInstance->time << std::endl;
	auto value = std::fmod(ManagerInstance->time,1.0f);
	
	glUniform1f(uloc, value);
		

	glUseProgram(0);

}