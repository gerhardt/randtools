#!/bin/bash
# 
# Copyright (c) 2018 Ilja Gerhardt, ilja@quantumlah.org
# 
# This program is free software: you can redistribute it and/or modify  
# it under the terms of the GNU General Public License as published by  
# the Free Software Foundation, version 3.
#
# This program is distributed in the hope that it will be useful, but 
# WITHOUT ANY WARRANTY; without even the implied warranty of 
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License 
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#


xxd -c10 -l 20 -b $1 | awk {'print $2 $3 $4 $5 $6 $7 $8 $9 $10 $11'} | tr -d \\n
