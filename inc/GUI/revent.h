
#ifndef REVENT_H
#define REVENT_H

namespace rtv
{

enum EventType
{
	RAPPFWEventNone,
	RAPPFWEventReshape,
	RAPPFWEventButtonClick,
	RAPPFWEventKeyPress,
	RAPPFWEventDraw,
	RAPPFWEXIT
};

class EventData
{
public:
	EventData()
	 : mType(RAPPFWEventNone)
	{}

	EventType mType;
	char mKey;
	int mX;
	int mY;
};

}

#endif
