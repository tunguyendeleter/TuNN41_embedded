/******************************************************************************
 * Project Name: 
 * File Name:   main.c
 *
 * Description: 
 *
 *              Target systems:           S32K144
 *              Derivatives:              ARM Cortex-M4
 *              Compiler:                 S32DS
 *
 *****************************************************************************/

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/

/******************************************************************************
 *  GLOBAL VARIABLE
 *****************************************************************************/
__attribute__((section (".UserData"))) int a = 5;
__attribute__((section (".UserData"))) unsigned char str[5] = "hihi";
__attribute__((section (".UserBss"))) int c = 0;


/******************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *****************************************************************************/


/******************************************************************************
 *  MAIN FUNCTION
 *****************************************************************************/
 
__attribute__((section (".UserCode"))) unsigned short STRLEN(unsigned char *string)
{
    unsigned short count = 0U;
    while (string[count] != '\0')
    {
        count++;
    }
    return count;
}

__attribute__((section (".UserCode"))) int STRCMP(unsigned char *string1, unsigned char *string2)
{
    unsigned short u16StrLen1 = STRLEN(string1);
    unsigned short u16StrLen2 = STRLEN(string2);
    unsigned short u16MinLen = (u16StrLen1 > u16StrLen2) ? (u16StrLen2) : (u16StrLen1);
    unsigned short u16MaxLen = (u16StrLen1 < u16StrLen2) ? (u16StrLen2) : (u16StrLen1);
    unsigned char i;
    int result = 0;

    for (i = 0; i < u16MinLen; i++)
    {
        if (string1[i] < string2[i])
        {
            return -1;
        }
        else if (string1[i] > string2[i])
        {
            return 1;
        }
    }

    if (u16MinLen != u16MaxLen)
    {
        result = (u16MinLen == u16StrLen1) ? -1 : 1;
    }

    return result;
}


int main(void)
{
    while (1)
    {
        STRLEN(str);
    }

    return 0;
}
