#pragma once
#include "MessageListener.h"

class MessageProducer
{
public:
	virtual ~MessageProducer() {}

	/**
	* Add a message listener to the listener list.
	* @param listener the message listener to add.
	*/
	virtual void add_message_listener(MessageListener *listener) = 0;

	/**
	* Send a message.
	* @param message the message to send.
	*/
	virtual void send_message(Message& message) const = 0;
};