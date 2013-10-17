
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
    RAPPFWEventResize,
	RAPPFWEventExit
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
    int mWidth;
    int mHeight;
};

}

#endif
