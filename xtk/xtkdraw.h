/*                                                                              
 * Copyright (C) 2013 Deepin, Inc.                                              
 *               2013 Zhai Xiang                                                
 *                                                                              
 * Author:     Zhai Xiang <zhaixiang@linuxdeepin.com>                           
 * Maintainer: Zhai Xiang <zhaixiang@linuxdeepin.com>                           
 *                                                                              
 * This program is free software: you can redistribute it and/or modify         
 * it under the terms of the GNU General Public License as published by         
 * the Free Software Foundation, either version 3 of the License, or            
 * any later version.                                                           
 *                                                                              
 * This program is distributed in the hope that it will be useful,              
 * but WITHOUT ANY WARRANTY; without even the implied warranty of               
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                
 * GNU General Public License for more details.                                 
 *                                                                              
 * You should have received a copy of the GNU General Public License            
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.        
 */              

#ifndef __XTKDRAW_H__
#define __XTKDRAW_H__

#include <gdk/gdk.h>

PangoFontDescription *font_desc_init(int size);
void font_desc_cleanup(PangoFontDescription *font_desc);
void draw_rect_stroke_to_cr(cairo_t *cr, 
                            int x, 
                            int y, 
                            int width, 
                            int height, 
                            GdkColor *color, 
                            double line_width);
void draw_rect_fill_to_cr(cairo_t *cr,                                        
                          int x,                                              
                          int y,                                              
                          int width,                                          
                          int height,                                         
                          GdkColor *color);                                    
void draw_rect_stroke_to_window(GdkWindow *window,                                           
                                int x,                                                       
                                int y,                                                    
                                int width,                                                
                                int height,                                               
                                char *color_spec, 
                                double line_width);    
void draw_rect_fill_to_window(GdkWindow *window,                              
                              int x,                                              
                              int y,                                          
                              int width,                                      
                              int height,                                     
                              char *color_spec);                               

#endif /* __XTKDRAW_H__ */
