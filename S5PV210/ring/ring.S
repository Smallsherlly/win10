.text
.code 32
.global Main

Main:
@配置基础参数
ldr r0,=0xE02000A0
ldr r1,=0x00000100
ldr r2,=0xfffff0ff
ldr r3,[r0]
and r3,r3,r2
orr r3,r3,r1
str r3,[r0]

ldr r0,=0xE02000A8
ldr r1,=0x00000000
ldr r2,=0xffffffcf
ldr r3,[r0]
and r3,r3,r2
orr r3,r3,r1
str r3,[r0]


@蜂鸣器打开
loop:
bl loop_ring
bl loop_time2
b loop


loop_ring:
mov r5,lr
mov r4,#16
loop_ring2:
subs r4,r4,#1
cmp r4,#0 
beq ring_end
ldr r0,=0xE02000A4    
ldr r1,=0x00000004
ldr r2,=0xfffffffb
ldr r3,[r0]
and r3,r3,r2
orr r3,r3,r1
str r3,[r0]

bl loop_time

ldr r0,=0xE02000A4    
ldr r1,=0x00000000
ldr r2,=0xfffffffb
ldr r3,[r0]
and r3,r3,r2
orr r3,r3,r1
str r3,[r0]

bl loop_time
b loop_ring2

loop_time:
ldr r0,=0x8000ffff
time:
subs r0,r0,#1
bpl time_end
b time

loop_time2:
ldr r0,=0x80300000
time2:
subs r0,r0,#1
bpl time_end
b time2

time_end:
mov pc,lr

ring_end:
mov pc,r5
