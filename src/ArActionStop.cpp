/*
Adept MobileRobots Robotics Interface for Applications (ARIA)
Copyright (C) 2004-2005 ActivMedia Robotics LLC
Copyright (C) 2006-2010 MobileRobots Inc.
Copyright (C) 2011-2015 Adept Technology, Inc.
Copyright (C) 2016-2018 Omron Adept Technologies, Inc.

     This program is free software; you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation; either version 2 of the License, or
     (at your option) any later version.

     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with this program; if not, write to the Free Software
     Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


*/
#include "Aria/ArExport.h"
#include "Aria/ariaOSDef.h"
#include "Aria/ArActionStop.h"
#include "Aria/ArRobot.h"

/**
   @param name name of the action
*/
AREXPORT ArActionStop::ArActionStop(const char *name) :
    ArAction(name, "Stops the robot")
{
}

AREXPORT ArActionStop::~ArActionStop()
{
}

AREXPORT ArActionDesired *ArActionStop::fire(
	UNUSED ArActionDesired currentDesired)
{
  myDesired.reset();

  myDesired.setVel(0);
  myDesired.setDeltaHeading(0);
  if (myRobot->hasLatVel())
    myDesired.setLeftLatVel(0);

  return &myDesired;
}
