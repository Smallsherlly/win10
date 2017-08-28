.text
.code 32
.global Main

Main:

@配置基础参数
ldr r0,=0xE0200240     
ldr r1,=0x00111000	
ldr r2,=0xff000fff
ldr r3,[r0]
and r3,r3,r2
orr r3,r3,r1
str r3,[r0]

ldr r0,=0xE02000A0
ldr r1,=0x00000010
ldr r2,=0xffffff0f
ldr r3,[r0]
and r3,r3,r2
orr r3,r3,r1
str r3,[r0]


ldr r0,=0xE0200248    
ldr r1,=0x00000000
ldr r2,=0xffff81ff
ldr r3,[r0]
and r3,r3,r2
orr r3,r3,r1
str r3,[r0]

ldr r0,=0xE02000A8
ldr r1,=0x00000000
ldr r2,=0xfffffff3
ldr r3,[r0]
and r3,r3,r2
orr r3,r3,r1
str r3,[r0]

@将所有灯熄灭
ldr r0,=0xE02000A4    
ldr r1,=0x00000002
ldr r2,=0xfffffffd
ldr r3,[r0]
and r3,r3,r2
orr r3,r3,r1
str r3,[r0]

ldr r0,=0xE0200244    
ldr r1,=0x00000038
ldr r2,=0xffffffc7
ldr r3,[r0]
and r3,r3,r2
orr r3,r3,r1
str r3,[r0]

bl loop_time

@流水灯循环
loop_led:
ldr r0,=0xE0200244    
ldr r1,=0x00000030
ldr r2,=0xffffffc7
ldr r3,[r0]
and r3,r3,r2
orr r3,r3,r1
str r3,[r0]

bl loop_time

ldr r0,=0xE0200244    
ldr r1,=0x00000028
ldr r2,=0xffffffc7
ldr r3,[r0]
and r3,r3,r2
orr r3,r3,r1
str r3,[r0]

bl loop_time

ldr r0,=0xE0200244    
ldr r1,=0x00000018
ldr r2,=0xffffffc7
ldr r3,[r0]
and r3,r3,r2
orr r3,r3,r1
str r3,[r0]

bl loop_time

ldr r0,=0xE0200244    
ldr r1,=0x00000038
ldr r2,=0xffffffc7
ldr r3,[r0]
and r3,r3,r2
orr r3,r3,r1
str r3,[r0]

ldr r0,=0xE02000A4    
ldr r1,=0x00000000
ldr r2,=0xfffffffd
ldr r3,[r0]
and r3,r3,r2
orr r3,r3,r1
str r3,[r0]

bl loop_time

ldr r0,=0xE02000A4    
ldr r1,=0x00000002
ldr r2,=0xfffffffd
ldr r3,[r0]
and r3,r3,r2
orr r3,r3,r1
str r3,[r0]

b loop_led

loop_time:
ldr r0,=0x80200000
time:
subs r0,r0,#1
bpl time_end
b time

time_end:
mov pc,lr

