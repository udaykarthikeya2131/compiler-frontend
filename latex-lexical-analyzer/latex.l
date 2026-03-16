%{
#define ENVB 1
#define ENVE 2
#define CMND_ 3
#define ME 4
#define DE 5
#define CMNT 6
%}

space     [ \t\n]
cmnd1     \\[a-zA-Z]+
cmnd2     \\.
spaces    {space}*
act_char  [~]
enve      \\[e][n][d]{spaces}[{].*[}]
envs      \\[b][e][g][i][n]{spaces}[{].*[}]
comment   [%].*

%%
{spaces}         {}
"\\["            {return DE;}
"\\]"            {return DE;}
{act_char}       {return CMND_;}
{enve}           {return ENVE;}
{envs}           {return ENVB;}
{cmnd1}          {return CMND_;}
{cmnd2}          {return CMND_;}
"$"              {return DE;}
"$$"              {return ME;}
{comment}        {return CMNT;}
.                {}
%%