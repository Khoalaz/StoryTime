#include "MessageHandler.h"

void MessageHandler::add_listener(MessageListener *listener)
{
	listeners.push_back(listener);
}

void MessageHandler::send_message(Message& message) const
{
	notify_listeners(message);
}

void MessageHandler::notify_listeners(Message& message) const
{
	for (MessageListener *listener : listeners) {
		listener->message_received(message);
	}
}