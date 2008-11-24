/*******************************************************************************
@TITLE      astroalgo.js
@VERSION    1.0.0
@LASTMOD    2003-Jan-15
@AUTHOR     Todd A. Guillory
@HISTORY    2002-11-04    created
@TODO       
********************************************************************************
COPYRIGHT NOTICE
Copyright (C) 2002 Barrios Technology, Inc.
Unauthorized duplication and/or use is strictly prohibited.
********************************************************************************
@USAGE
Include this file in the header of the page to use rollovers
<SCRIPT LANGUAGE="JavaScript" SRC="astroalgo.js"></SCRIPT>

*******************************************************************************/
// DaysInMonth
// Returns the number of days in month inMonth and year inYear
function DaysInMonth(inMonth, inYear)
{
	this.year = inYear;
	this.totalDays = new Array(31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31);
	this.month = (inMonth < 1) ? 1 : inMonth;
	this.month = (inMonth > 12) ? 12 : this.month;

	if ( this.year >= 0 )
	{
		this.totalDays[1] = (this.year % 400 == 0 || this.year % 4 == 0 && this.year % 100 != 0) ? 29 : 28;
	}
	else
	{
		this.totalDays[1] = (this.year % 4 == 0) ? 29 : 28;
	}
	
	return totalDays[this.month-1];
}