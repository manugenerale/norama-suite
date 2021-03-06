/*
 * norama suite - Panorama tools suite
 *
 * Copyright (c) 2013-2015 FOXEL SA - http://foxel.ch
 * Please read <http://foxel.ch/license> for more information.
 *
 *
 * Author(s):
 *
 *      Nils Hamel <n.hamel@foxel.ch>
 *
 *
 * This file is part of the FOXEL project <http://foxel.ch>.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * Additional Terms:
 *
 *      You are required to preserve legal notices and author attributions in
 *      that material or in the Appropriate Legal Notices displayed by works
 *      containing it.
 *
 *      You are required to attribute the work as explained in the "Usage and
 *      Attribution" section of <http://foxel.ch/license>.
 */

    /*! \file   norama-view.h
     *  \author Nils Hamel <n.hamel@foxel.ch>
     *   
     *  Software main header
     */

    /*! \mainpage norama-view
     *
     *  \section norama-suite
     *  \section _ Panorama tools suite
     *
     *  This software suite offers tools for numerical panoramas manipulation.
     *  Mostly designed for equirectangular mappings, its role is to provide an
     *  interface to libgnomonic and its algorithms. It then offers an interface
     *  to projection and transformation features implemented in the gnomonic
     *  library. The norama-suite is also interfaced with libcsps in order to 
     *  take advantage of camera motion tracking to operate and align panoramas
     *  on earth. It also comes with a panorama viewer to complete the suite.
     *
     *  \section Documentation
     *
     *  A detailed documentation can be generated through doxygen. A more general
     *  documentation can be consulted at https://github.com/FoxelSA/norama-suite/wiki
     *
     *  \section Copyright
     * 
     *  Copyright (c) 2013-2015 FOXEL SA - http://foxel.ch \n
     *  This program is part of the FOXEL project <http://foxel.ch>.
     *  
     *  Please read the COPYRIGHT.md file for more information.
     *
     *  \section License
     *
     *  This program is licensed under the terms of the GNU Affero General Public
     *  License v3 (GNU AGPL), with two additional terms. The content is licensed
     *  under the terms of the Creative Commons Attribution-ShareAlike 4.0
     *  International (CC BY-SA) license.
     *
     *  You must read <http://foxel.ch/license> for more information about our
     *  Licensing terms and our Usage and Attribution guidelines.
     */

/* 
    Header - Include guard
 */

    # ifndef __NR_VIEW__
    # define __NR_VIEW__

/* 
    Header - C/C++ compatibility
 */

    # ifdef __cplusplus
    extern "C" {
    # endif

/* 
    Header - Includes
 */

    # include <stdio.h>
    # include <stdlib.h>
    # include <X11/Xlib.h>
    # include <opencv/cv.h>
    # include <opencv/highgui.h>
    # include <gnomonic-all.h>
    # include <common-all.h>

/* 
    Header - Preprocessor definitions
 */

    /* Standard help */
    # define NR_HELP "Usage summary :\n\n"                 \
    "\tnorama-view [Arguments] [Parameters] ...\n\n"       \
    "Short arguments and parameters summary :\n\n"         \
    "\t-i\tInput equirectangular mapping image\n"          \
    "\t-s\tScale applied on display buffer\n"              \
    "\t-x\tScreen horizontal pixel count\n"                \
    "\t-y\tScreen vertical pixel count\n"                  \
    "\t-t\tNumber of threads\n\n"                          \
    "norama-view - norama-suite\n"                         \
    "Copyright (c) 2013-2015 FOXEL SA - http://foxel.ch\n"

    /* Define keyevent codes */
    # define NR_KEY_ESCAPE   27
    # define NR_KEY_F       102
    # define NR_KEY_R       114

    /* Define default values */
    # define NR_DFT_SCALE   1.0
    # define NR_DFT_THREAD    8

    /* Define mouse motion mode */
    # define NR_MS_NONE       0
    # define NR_MS_MOVE       1
    # define NR_MS_ZOOM       2  

    /* Define FOV constants */
    # define NR_MIN_APPER   (  20.0 * ( LG_PI / 180.0 ) )
    # define NR_MAX_APPER   ( 120.0 * ( LG_PI / 180.0 ) )
    # define NR_DFT_APPER   ( 100.0 * ( LG_PI / 180.0 ) )

/* 
    Header - Preprocessor macros
 */

/* 
    Header - Typedefs
 */

/* 
    Header - Structures
 */

    /*! \struct nr_Mouse_struct
     *  \brief Mouse control structure
     *  
     *  This structure is used to ensure communication between display function
     *  and the mouse event callback function.
     *  
     *  \var nr_Mouse_struct::msAzim
     *  Display view azimuth angle, in radian
     *  \var nr_Mouse_struct::msElev
     *  Display view elevation angle, in radian
     *  \var nr_Mouse_struct::msAppe
     *  Display view gnomonic aperture, in radian
     *  \var nr_Mouse_struct::msWidth
     *  Mapping width broadcasting variable for motion weighting
     */

    typedef struct nr_Mouse_struct {

        double msAzim;
        double msElev;
        double msAppe;
        double msWidth;

    } nr_Mouse;

/* 
    Header - Function prototypes
 */

    /*! \brief Software main function
     *  
     *  The main function is responsible for panoramic image loading and the
     *  management of the display. A pseudo-infinite loop is handled by the main
     *  function in which mouse and keyboard events are managed. The computation
     *  of the display buffer is also performed in this loop.
     *  
     *  \param argc Standard main parameter
     *  \param argv Standard main parameter
     */

    int main ( int argc, char ** argv );

    /*! \brief Mouse callback
     *
     *  This function is the mouse event callback that is used throught OpenCV
     *  library. It is responsible for display view motion based on mouse move.
     *
     *  \param event    Mouse event code
     *  \param x        Mouse position x at event
     *  \param y        Mouse position y at event
     *  \param flag     Mouse event flag
     *  \param userdata Userdata handle, used for motion management
     */

    void nr_view_mouse ( int event, int x, int y, int flag, void * userdata );

    /*! \brief Screen resolution
     *
     *  This function allows to obtain the current screen resolution. The width
     *  and height, in pixels, are returned using the variable pointers given as
     *  parameter.
     *
     *  The scale parameter is applied on the two screen dimension. This is done
     *  in order to be able to reduce the display buffer size when the local
     *  computer is not enough powerful for the desired rendering.
     *
     *  If the function fails to get the screen resolution, it returns a default
     *  screen resolution that corresponds to the statistically most used one at
     *  the time this line is written.
     *
     *  \param nrWidth  Buffer that recieves the screen width
     *  \param nrHeight Buffer that recieves the screen height
     *  \param nrScale  Screen dimension scale factor
     */

    void nr_view_display ( int * nrWidth, int * nrHeight, float nrScale );

/* 
    Header - C/C++ compatibility
 */

    # ifdef __cplusplus
    }
    # endif

/*
    Header - Include guard
 */

    # endif

