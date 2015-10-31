/*********************************************************************
* 版权所有 (C)2015, Zhou Zhaoxiong。
*
* 文件名称：GetSecNumBetweenTwoYear.c
* 文件标识：无
* 内容摘要：获取当前时间到1970年之前某时间的秒数
* 其它说明：无
* 当前版本：V1.0
* 作    者：Zhou Zhaoxiong
* 完成日期：20150211
*
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned short int  UINT16;
typedef signed   int        INT32;
typedef unsigned int        UINT32;


UINT32 GetSecNumBetweenTwoYear(UINT16 iFirstYear, UINT16 iSecondYear);

/*********************************************************************
* 功能描述：主函数
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：无
* 修改日期         版本号       修改人         修改内容
* -------------------------------------------------------------------
* 20150211        V1.0     Zhou Zhaoxiong        创建
*********************************************************************/
INT32 main()
{
    UINT32 iYearBefore1970 = 0;
    UINT32 iSecondsTo1970  = 0;
    UINT32 iTotalSeconds   = 0;

    // 先输入一个1970年之前的年份
    printf("Please input a year before 1970: \n");
    scanf("%d", &iYearBefore1970);
    if (iYearBefore1970 >= 1970)    // 确保输入时间小于1970
    {
        printf("The year %d isn't less than 1970, please check!\n", iYearBefore1970);
        return -1;
    }

    // 计算输入年份到1970年的秒数
    iSecondsTo1970 = GetSecNumBetweenTwoYear(iYearBefore1970, 1970);
    printf("The total seconds from %d to 1970 is: %u\n", iYearBefore1970, iSecondsTo1970);

    // 计算总的秒数
    iTotalSeconds = (UINT32)(time(0) + (time_t)iSecondsTo1970);
    printf("The total seconds from %d to now is: %u\n", iYearBefore1970, iTotalSeconds);

    return 0;                  // main函数返回0
}


/**********************************************************************
* 功能描述： 计算任意两年之间的秒数
* 输入参数： iFirstYear-减数
            iSecondYear-被减数
* 输出参数： 无
* 返 回 值： 秒数
* 其它说明： 无
* 修改日期         版本号          修改人        修改内容
* --------------------------------------------------------------------
* 20150211         V1.0      Zhou Zhaoxiong        创建
*********************************************************************/
UINT32 GetSecNumBetweenTwoYear(UINT16 iFirstYear, UINT16 iSecondYear)
{
    UINT32 iTotalDays = 0;      // 两年之间的总天数
    UINT16 iTmpYear   = 0;      // 用作临时存放中间数据

    // 输入参数检查, 保证减数小于被减数
    if (iFirstYear > iSecondYear) 
    {
        iTmpYear    = iFirstYear;
        iFirstYear  = iSecondYear;
        iSecondYear = iTmpYear;
    }

    // 计算总天数
    iTotalDays = 0;

    for (iTmpYear = iFirstYear; iTmpYear < iSecondYear; iTmpYear ++)
    {
        // 判断该年天数:1-能被4整除,但不能被100整除的是闰年; 2-能被400整除的是闰年
        if ((0 == (iTmpYear%4) && 0 != (iTmpYear%100)) || 
             0 == (iTmpYear%400))
        {
            iTotalDays += 366;    // 闰年
        }
        else
        {
            iTotalDays += 365;    // 平年
        }
    }

    return iTotalDays * 86400;    // 总的秒数
}
