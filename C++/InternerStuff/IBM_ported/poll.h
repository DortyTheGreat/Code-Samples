/***********************************************************************************************/
/*                                                                                             */
/*                                      File : poll.h                                          */
/*                                                                                             */
/*                      poll UNIX function implementation for WINDOWS                          */
/*                                                                                             */
/*                                                                                             */
/***********************************************************************************************/
/**
 * Copyright (C) 2016 Benoit Rock
 *                    rock.s.architecture.free.fr/poll.html
 *
 * Rock's Architecture is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _POLL_H__
#define _POLL_H__


#include <winsock2.h>

struct pollfd
 {
	SOCKET fd;				// File descriptor to poll.  
    short int events;		// Types of events poller cares about.  
    short int revents;		// Types of events that actually occurred.  
  };

int poll(struct pollfd *tabPollfd, unsigned long size, int timeOut);

#endif
