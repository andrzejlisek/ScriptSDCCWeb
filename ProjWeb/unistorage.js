function LS()
{
    try
    {
        if (localStorage)
        {
            const test = "test" + new Date().valueOf();
            try
            {
                localStorage.setItem(test, test);
                localStorage.removeItem(test);
                return true;
            }
            catch(e)
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    catch (X)
    {
        return false;
    }
}


function DataExists(name)
{
    if (LS())
    {
        if (localStorage[name])
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

function DataGet(name)
{
    if (LS())
    {
        return localStorage.getItem(name);
    }
    else
    {
        return "";
    }
}


function DataSet(name, val)
{
    if (LS())
    {
        localStorage.setItem(name, val);
    }
}

function DataDelete(name)
{
    if (DataExists(name))
    {
        localStorage.removeItem(name)
    }
}

function DataRaw()
{
    let raw = "";
    if (LS())
    {
        for (let item in localStorage)
        {
            raw += (item + "=" + localStorage.getItem(item) + "\n" );
        }
    }
    return raw;
}

function DataClear(prefix)
{
    if (LS())
    {
        if (prefix.length > 0)
        {
            let items = [];        
            for (let item in localStorage)
            {
                if (item.length >= prefix.length)
                {
                    if (item.substr(0, prefix.length) == prefix)
                    {
                        items.push(item);
                    }
                }
            }
            for (let I = 0; I < items.length; I++)
            {
                DataDelete(items[I]);
            }
        }
        else
        {
            localStorage.clear();
        }
    }
}

function DataSetI(name, val)
{
    DataSet(name, val);
}

function DataGetI(name)
{
    return parseInt(DataGet(name));
}

function DataSetB(name, val)
{
    DataSet(name, val ? "1" : "0");
}

function DataGetB(name)
{
    return (DataGet(name) == "1");
}

function DataGetDefault(name, val)
{
    if (DataExists(name))
    {
        return DataGet(name);
    }
    else
    {
        return val;
    }
}

function DataGetIDefault(name, val)
{
    if (DataExists(name))
    {
        return DataGetI(name);
    }
    else
    {
        return val;
    }
}

function DataGetBDefault(name, val)
{
    if (DataExists(name))
    {
        return DataGetB(name);
    }
    else
    {
        return val;
    }
}

