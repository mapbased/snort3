//--------------------------------------------------------------------------
// Copyright (C) 2014-2017 Cisco and/or its affiliates. All rights reserved.
// Copyright (C) 2004-2013 Sourcefire, Inc.
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License Version 2 as published
// by the Free Software Foundation.  You may not use, modify or distribute
// this program under any other version of the GNU General Public License.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//--------------------------------------------------------------------------

#ifndef PS_DETECT_H
#define PS_DETECT_H

#include <sys/time.h>
#include <time.h>

#include "sfip/sf_ip.h"
#include "ipobj.h"

#define PS_OPEN_PORTS 8

struct PsCommon
{
    unsigned long memcap;

    PsCommon() { memcap = 0; }
};

struct PS_ALERT_CONF
{
    short connection_count;
    short priority_count;
    short u_ip_count;
    short u_port_count;
};

struct PortscanConfig
{
    int detect_scans;
    int detect_scan_type;
    int proto_cnt;
    int include_midstream;
    int print_tracker;

    bool logfile;

    unsigned tcp_window;
    unsigned udp_window;
    unsigned ip_window;
    unsigned icmp_window;

    IPSET* ignore_scanners;
    IPSET* ignore_scanned;
    IPSET* watch_ip;

    PsCommon* common;

    PS_ALERT_CONF tcp_ports;
    PS_ALERT_CONF tcp_decoy;
    PS_ALERT_CONF tcp_sweep;
    PS_ALERT_CONF tcp_dist;

    PS_ALERT_CONF udp_ports;
    PS_ALERT_CONF udp_decoy;
    PS_ALERT_CONF udp_sweep;
    PS_ALERT_CONF udp_dist;

    PS_ALERT_CONF ip_proto;
    PS_ALERT_CONF ip_decoy;
    PS_ALERT_CONF ip_sweep;
    PS_ALERT_CONF ip_dist;

    PS_ALERT_CONF icmp_sweep;

    PortscanConfig();
    ~PortscanConfig();
};

struct PS_PROTO
{
    int connection_count;
    int priority_count;
    int u_ip_count;
    int u_port_count;

    unsigned short high_p;
    unsigned short low_p;
    unsigned short u_ports;

    SfIp high_ip;
    SfIp low_ip;
    SfIp u_ips;

    unsigned short open_ports[PS_OPEN_PORTS];
    unsigned char open_ports_cnt;

    struct timeval event_time;
    unsigned int event_ref;

    unsigned char alerts;

    time_t window;
};

struct PS_TRACKER
{
    int priority_node;
    int protocol;
    PS_PROTO proto;
};

struct PS_PKT
{
    void* pkt;

    PS_TRACKER* scanner;
    PS_TRACKER* scanned;

    int proto;
    int reverse_pkt;
};

//-------------------------------------------------------------------------

#define PS_PROTO_NONE        0x00
#define PS_PROTO_TCP         0x01
#define PS_PROTO_UDP         0x02
#define PS_PROTO_ICMP        0x04
#define PS_PROTO_IP          0x08
#define PS_PROTO_ALL         0x0f

#define PS_PROTO_OPEN_PORT   0x80

#define PS_TYPE_PORTSCAN     0x01
#define PS_TYPE_PORTSWEEP    0x02
#define PS_TYPE_DECOYSCAN    0x04
#define PS_TYPE_DISTPORTSCAN 0x08
#define PS_TYPE_ALL          0x0f

#define PS_SENSE_HIGH        3
#define PS_SENSE_MEDIUM      2
#define PS_SENSE_LOW         1

#define PS_ALERT_ONE_TO_ONE                1
#define PS_ALERT_ONE_TO_ONE_DECOY          2
#define PS_ALERT_PORTSWEEP                 3
#define PS_ALERT_DISTRIBUTED               4
#define PS_ALERT_ONE_TO_ONE_FILTERED       5
#define PS_ALERT_ONE_TO_ONE_DECOY_FILTERED 6
#define PS_ALERT_DISTRIBUTED_FILTERED      7
#define PS_ALERT_PORTSWEEP_FILTERED        8
#define PS_ALERT_OPEN_PORT                 9

#define PS_ALERT_GENERATED                 255

#endif

