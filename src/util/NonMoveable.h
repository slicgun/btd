#pragma once

class NonMoveable
{
public:
	NonMoveable() = default;
	NonMoveable(const NonMoveable&) = default;
	NonMoveable& operator=(const NonMoveable&) = default;

	NonMoveable(NonMoveable&&) = delete;
	NonMoveable& operator=(NonMoveable&&) = delete;

	virtual ~NonMoveable() = default;
};