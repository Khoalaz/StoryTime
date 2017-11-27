#pragma once

#include "Message.h"

class MessageListener
{
public:
	virtual ~MessageListener() {}

	/**
	* Receive a message sent by a message producer.
	* @param message the message that was received.
	*/
	virtual void message_received(Message& message) = 0;
};
