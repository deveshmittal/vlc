/*
 * PlaylistManager.h
 *****************************************************************************
 * Copyright © 2010 - 2011 Klagenfurt University
 *             2015 VideoLAN Authors
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#ifndef PLAYLISTMANAGER_H_
#define PLAYLISTMANAGER_H_

#include "logic/AbstractAdaptationLogic.h"
#include "Streams.hpp"

namespace adaptative
{
    namespace playlist
    {
        class AbstractPlaylist;
    }

    namespace http
    {
        class HTTPConnectionManager;
    }

    using namespace playlist;
    using namespace logic;
    using namespace http;

    class PlaylistManager
    {
        public:
            PlaylistManager( AbstractPlaylist *,
                             AbstractAdaptationLogic::LogicType type, stream_t *stream);
            virtual ~PlaylistManager    ();

            bool    start         (demux_t *);
            size_t  read();
            mtime_t getDuration() const;
            mtime_t getPCR() const;
            int     getGroup() const;
            int     esCount() const;
            bool    setPosition(mtime_t);
            bool    seekAble() const;
            virtual bool updatePlaylist();

        protected:
            virtual AbstractAdaptationLogic *createLogic(AbstractAdaptationLogic::LogicType);

            HTTPConnectionManager              *conManager;
            AbstractAdaptationLogic::LogicType  logicType;
            AbstractPlaylist                    *playlist;
            stream_t                            *stream;
            Streams::Stream                     *streams[Streams::count];
            mtime_t                              nextPlaylistupdate;
    };

}

#endif /* PLAYLISTMANAGER_H_ */
