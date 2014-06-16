/*
** Copyright (C) 2014 Cisco and/or its affiliates. All rights reserved.
 * Copyright (C) 2002-2013 Sourcefire, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License Version 2 as
 * published by the Free Software Foundation.  You may not use, modify or
 * distribute this program under any other version of the GNU General
 * Public License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
// converter.h author Josh Rosenbaum <jorosenba@cisco.com>

#ifndef CONVERSION_STATE_H
#define CONVERSION_STATE_H

#include <string>
#include <fstream>
#include <sstream>

#include "converter.h"
 
class ConversionState
{

public:
    ConversionState(Converter *cv){ converter = cv; }
    virtual ~ConversionState() {};
    virtual bool convert(std::stringstream& data)=0;

protected:
    Converter* converter;

    inline bool parse_int_option(std::string opt_name, std::stringstream& stream)
    {
        int val;

        if(stream >> val)
        {
            converter->add_option_to_table(opt_name, val);
            return true;
        }

        converter->add_comment_to_table("snort.conf missing argument for: " + opt_name + " <int>");
        return false;
    }

    // parse adn add a curly bracketed list to the table
    inline bool parse_curly_bracket_list(std::string list_name, std::stringstream& stream)
    {
        std::string elem;
        bool retval = true;

        if(!(stream >> elem) || (elem != "{"))
            return false;

        while (stream >> elem && elem != "}")
            retval = converter->add_list_to_table(list_name, elem) && retval;

        return retval;
    }

    // parse and add a yes/no boolean option.
    inline bool parse_yn_bool_option(std::string opt_name, std::stringstream& stream)
    {
        std::string val;

        if(!(stream >> val))
            return false;

        else if(!val.compare("yes"))
            return converter->add_option_to_table(opt_name, true);

        else if (!val.compare("no"))
            return converter->add_option_to_table(opt_name, false);

        converter->add_comment_to_table("Unable to convert_option: " + opt_name + ' ' + val);
        return false;
    }

private:

};


typedef ConversionState* (*conv_new_f)(Converter*);

struct ConvertMap
{
    std::string keyword;
    conv_new_f ctor;
};




#endif
