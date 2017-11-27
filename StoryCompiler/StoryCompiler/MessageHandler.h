#pragma once

#include <vector>
#include "MessageListener.h"

using namespace std;

class MessageHandler
{
public:
	/**
	* Add a listener to the listener list.
	* @param listener the listener to add.
	*/
	void add_listener(MessageListener *listener);

	/**
	* Send a message.
	* @param message the message to send.
	*/
	void send_message(Message& message) const;

private:
	vector<MessageListener *> listeners;

	/**
	* Notify each listener in the listener list by calling the listener's
	* messageReceived() method.
	* @param message the message to be received.
	*/
	void notify_listeners(Message& message) const;
};