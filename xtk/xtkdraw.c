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

#include "xtkdraw.h"

PangoFontDescription *font_desc_init(int size) 
{
    PangoFontDescription *font_desc = NULL;

    font_desc = pango_font_description_new();
    if (!font_desc) 
        return NULL;

    pango_font_description_set_family(font_desc, "WenQuanYi");
    pango_font_description_set_style(font_desc, PANGO_STYLE_NORMAL);
    pango_font_description_set_weight(font_desc, PANGO_WEIGHT_NORMAL);
    pango_font_description_set_stretch(font_desc, PANGO_STRETCH_NORMAL);
    pango_font_description_set_size(font_desc, size);

    return font_desc;
}

void font_desc_cleanup(PangoFontDescription *font_desc) 
{
    if (!font_desc) 
        return;

    pango_font_description_free(font_desc);
    font_desc = NULL;
}

void draw_rect_stroke_to_cr(cairo_t *cr,                                              
                            int x,                                                    
                            int y,                                                    
                            int width,                                                
                            int height,                                              
                            GdkColor *color,                                      
                            double line_width) 
{
    if (line_width == 1.0)                                                      
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_NONE);                          
                                                                                
    cairo_set_line_width(cr, line_width);                                       
    gdk_cairo_set_source_color(cr, &color);
    cairo_rectangle(cr, x, y, width, height);                                   
    cairo_stroke(cr);     
}

void draw_rect_fill_to_cr(cairo_t *cr,                                            
                          int x,                                                  
                          int y,                                                  
                          int width,                                              
                          int height,                                             
                          GdkColor *color)                                    
{                                                                               
    gdk_cairo_set_source_color(cr, &color);                                     
    cairo_rectangle(cr, x, y, width, height);                                   
    cairo_fill(cr);                                                           
}                       

void draw_rect_stroke_to_window(GdkWindow *window, 
                                int x,                              
                                int y,                                           
                                int width,                                       
                                int height,                                      
                                char *color_spec, 
                                double line_width) 
{
    cairo_t *cr = NULL;                   
    GdkColor color;                                                             
                                                                                
    cr = gdk_cairo_create(window);                                              
    if (!cr)                                                                    
        return;                                                         

    gdk_color_parse(color_spec, &color);
    draw_rect_stroke_to_cr(cr, x, y, width, height, &color, line_width);
                                                                                
    if (cr) {                                                                   
        cairo_destroy(cr);                                                      
        cr = NULL;                                                              
    }                
}

void draw_rect_fill_to_window(GdkWindow *window,                              
                              int x,                                          
                              int y,                                          
                              int width,                                      
                              int height,                                     
                              char *color_spec)                       
{                                                                               
    cairo_t *cr = NULL;                                                         
    GdkColor color;                                                             
                                                                                
    cr = gdk_cairo_create(window);                                              
    if (!cr)                                                                    
        return;                                                                 
                                                                                
    gdk_color_parse(color_spec, &color);                                        
    draw_rect_fill_to_cr(cr, x, y, width, height, &color);        
                                                                                
    if (cr) {                                                                   
        cairo_destroy(cr);                                                      
        cr = NULL;                                                              
    }                                                                           
}               
