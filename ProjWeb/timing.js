const TimingLenMax = 5;

function TimingPrepare(Idx)
{
    StorageMemo[Idx].TimingLen = 0;
    StorageMemo[Idx].TimingTime = [];
    StorageMemo[Idx].TimingCmds = [];
    StorageMemo[Idx].TimingVal = "";
}

function TimingReset(Idx)
{
    StorageMemo[Idx].TimingLen = 0;
    StorageMemo[Idx].TimingTime = [];
    StorageMemo[Idx].TimingCmds = [];
    StorageMemo[Idx].TimingVal = "";
}

function TimingSet(Idx, Cmds)
{
    if (StorageMemo[Idx].TimingLen >= TimingLenMax)
    {
        StorageMemo[Idx].TimingTime.shift();
        StorageMemo[Idx].TimingCmds.shift();
        StorageMemo[Idx].TimingLen--;
    }
    StorageMemo[Idx].TimingTime.push(performance.now());
    StorageMemo[Idx].TimingCmds.push(Cmds);
    StorageMemo[Idx].TimingLen++;
    let TimingVal = 0;
    for (let I = 1; I < StorageMemo[Idx].TimingLen; I++)
    {
        TimingVal = TimingVal + StorageMemo[Idx].TimingCmds[I];
    }
    const TimingT = StorageMemo[Idx].TimingTime[StorageMemo[Idx].TimingLen - 1] - StorageMemo[Idx].TimingTime[0];
    if (TimingT > 0)
    {
        TimingVal = Math.round(TimingVal * 1000 / TimingT);
    }
    else
    {
        TimingVal = 0;
    }

    let Unit = " IPS";
    if (TimingVal >= 10000000)
    {
        Unit = " MIPS";
        TimingVal = Math.round(TimingVal / 1000000);
    }
    else
    {
        if (TimingVal >= 10000)
        {
            Unit = " kIPS";
            TimingVal = Math.round(TimingVal / 1000);
        }
    }

    let TimingVal_ = TimingVal + "";
    let SpacePos = TimingVal_.length - 3;
    if (SpacePos > 0) { TimingVal_ = TimingVal_.substr(0, SpacePos) + " " + TimingVal_.substr(SpacePos); }
    SpacePos -= 3;
    if (SpacePos > 0) { TimingVal_ = TimingVal_.substr(0, SpacePos) + " " + TimingVal_.substr(SpacePos); }

    StorageMemo[Idx].TimingVal = TimingVal_ + Unit;
}

