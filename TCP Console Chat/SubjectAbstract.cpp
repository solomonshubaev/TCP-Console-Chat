#include "SubjectAbstract.h"

SubjectAbstract::~SubjectAbstract()
{
	for (ObserverAbstract* observer : this->observers)
	{
		delete observer;
	}
}

void SubjectAbstract::attach(ObserverAbstract* observer)
{
	this->observers.push_back(observer);
}

void SubjectAbstract::detach(ObserverAbstract* observer)
{
	auto iterator = std::find(this->observers.begin(), this->observers.end(), observer);
	if (iterator != this->observers.end())
	{
		this->observers.erase(iterator);
		delete observer; // Do I want to delete the pointer from here? Do I need?
	}
}
