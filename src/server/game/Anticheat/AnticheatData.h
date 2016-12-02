/* WotLKFunCore is a custom fun server built for
* World of Warcarft game build 3.3.5b. (12345)
*
* Copyright (C) 2008-2016 JustACore.
*
* ==== Start of GNU GPL ====
*
* This file is free software; as a special exception the author gives
* unlimited permission to copy and/or distribute it, with or without
* modifications, as long as this notice is preserved.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* ==== End of GNU GPL ====
*/

#ifndef SC_ACDATA_H
#define SC_ACDATA_H

#include "AnticheatMgr.h"

#define MAX_REPORT_TYPES 6

class AnticheatData
{
public:
    AnticheatData();
    ~AnticheatData();

    void SetLastOpcode(uint32 opcode);
    uint32 GetLastOpcode() const;

    const MovementInfo& GetLastMovementInfo() const;
    void SetLastMovementInfo(MovementInfo& moveInfo);

    void SetPosition(float x, float y, float z, float o);

    /*
    bool GetDisableACCheck() const;
    void SetDisableACCheck(bool check);

    uint32 GetDisableACTimer() const;
    void SetDisableACTimer(uint32 timer);*/

    uint32 GetTotalReports() const;
    void SetTotalReports(uint32 _totalReports);

    uint32 GetTypeReports(uint32 type) const;
    void SetTypeReports(uint32 type, uint32 amount);

    float GetAverage() const;
    void SetAverage(float _average);

    uint32 GetCreationTime() const;
    void SetCreationTime(uint32 creationTime);

    void SetTempReports(uint32 amount, uint8 type);
    uint32 GetTempReports(uint8 type);

    void SetTempReportsTimer(uint32 time, uint8 type);
    uint32 GetTempReportsTimer(uint8 type);

    void SetDailyReportState(bool b);
    bool GetDailyReportState();
private:
    uint32 lastOpcode;
    MovementInfo lastMovementInfo;
    //bool disableACCheck;
    //uint32 disableACCheckTimer;
    uint32 totalReports;
    uint32 typeReports[MAX_REPORT_TYPES];
    float average;
    uint32 creationTime;
    uint32 tempReports[MAX_REPORT_TYPES];
    uint32 tempReportsTimer[MAX_REPORT_TYPES];
    bool hasDailyReport;
};

#endif