%{
 #define Id 1
 #define Num 2
 #define Op 3
 #define lb 4
 #define rb 5

%}
space [ \t\n]
spacces {space}+
digit [0-9]
name [a-zA-Z_]
names {name}+
digits {digit}+
name_command \\[a-zA-Z]+
num_id [a-zA-Z0-9]+
ID [a-zA-Z]{num_id}?
NUM [+-]?{digit}+
OP [+-/*%]


%%
{ID} {return (Id);}
{NUM} {return (Num);}
{OP} {return (Op);}
{spacces} {}
"(" {return (lb);}
")" {return (rb);}


%%
