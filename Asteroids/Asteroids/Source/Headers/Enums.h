#include "stdafx.h"
#include "player.h"

#ifndef ENUMS_H
#define ENUMS_H
class Enumerated_Lists
{
private:

public:
	struct Keys
	{
		enum Type
		{
			KEY_UP,
			KEY_DOWN,
			KEY_LEFT,
			KEY_RIGHT
		};
		Type t_;
		Keys(Type t) : t_(t) {}
		operator Type () const { return t_; }
	private:
		template<typename T>
		operator T () const;
	};
	bool key[4];

	struct Params
	{
		enum Type
		{
			FULLSCREEN,
			CONSOLE
			//,RESOLUTION
		};
		Type t_;
		Params(Type t) : t_(t) {}
		operator Type () const { return t_; }
	private:
		template<typename T>
		operator T () const;
	}; 
	bool args[4];
};
#endif