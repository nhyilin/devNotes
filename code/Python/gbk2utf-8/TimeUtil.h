

/*	将整数表示的月份转换成字符串表示的月份

	** 输入:
	**		im:	整数表示的月份(1 - 12)

	** 输出:
	**		字符串表示的月份，Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec
*/
string MonthIntToStr(int im);



/*	计算儒略日

	** 输入:
	**		MJDInSecond:	秒时间，等于约当儒略日（MJD）乘以每日的秒数（86400.0）

	** 输出:
	**		MJDInSecond 对应的儒略日
*/
double ComputeJD( double MJDInSecond );


/*	计算儒略日（重载）

	** 输入:
	**		szCalendar:		日历字符串，格式：dd mmm yyyy HH:MM:SS.FFF

	** 输出:
	**		szCalendar 对应的儒略日
*/
double ComputeJD(const char* szCalendar);


/*	计算约当儒略日

	** 输入:
	**		MJDInSecond:	秒时间，等于约当儒略日（MJD）乘以每日的秒数（86400.0）

	** 输出:
	**		MJDInSecond 对应的约当儒略日
*/
double ComputeMJD( double MJDInSecond );

