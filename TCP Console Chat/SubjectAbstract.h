#pragma once
#ifndef SUBJECT_ABSTRACT
#define SUBJECT_ABSTRACT
#include "ObserverAbstract.h"
#include <vector>

class SubjectAbstract
{
protected:
	std::vector<ObserverAbstract*> observers; // Optional - Maybe all this class should ne Interface rather than Abstract

public:
	virtual ~SubjectAbstract();
	virtual void attach(ObserverAbstract* observer);
	virtual void detach(ObserverAbstract* observer);
	virtual void notify() { };
};
#endif // SUBJECT_ABSTRACT
