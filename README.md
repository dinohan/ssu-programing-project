﻿# 소코반 프로젝트

## 팀원

> 이강준 20192852
>
> **이재호** 20192860
>
> 정준서 20192873
>
> 한도협 20192880

## 프로그램

* [main.c](./main.c)
* [map.txt](./map.txt)
* [ranking.txt](./ranking.txt)
* [sokoban.txt](./sokoban.txt)

## [Notion](https://www.notion.so/dinohan/Sokoban-8149ab2adfbf4249a073d10d1d1a2970)

##	[문제 설명](./project.pdf)

* **목적** : 소코반 게임을 프로그래밍 함으로써 C 프로그래밍 기법을 익히고 프로그래밍 능력 향상
* **팀** : 4인 1팀
* **제출물** : 하드카피(프로그램 개요, 프로그램 소스, 실행 화면), 모든 제출물은 스마트캠퍼스로도 제출. 스마트캠퍼스에 제출할 때 각 파일을 기본 `.zip` 프로그램으로 묶고 파일 이름은 대표 학생 학번으로 할 것
* **기한** : 6월 9일 일요일

### 요구조건

0. 프로그램 검사는 요구 조건에 기술된 대로 함. 즉, **요구 조건**을 따르지 않으면 **0점** 처리됨

1. 맵은 최대 5개가 저장된 파일에서 읽어드림. 맵 파일의 파일명은 `map`으로 하고 다음과 같은 형식으로 저장함(`@`: 창고지기, `#` : 벽, `$` : 박스(금), `O`: 보관장소, 숫자(레벨) : 새로운 맵 시작, `e` : 맵 끝, `.` : blank). 단, 각 맵의 가로와 세로 길이는 각각 최대 `30` 임

2. `map`을 읽은 다음 각 레벨별로 박스`$`의 개수와 보관장소`O` 개수가 같은지 확인하고 같지 않다면 오류 메시지를 출력하고 종료함 

3. 프로그램이 시작되면 먼저 **사용자 이름**을 입력받음(영문 최대 `10`문자) 

4. 게임은 입력된 맵을 모두 완수하면 축하메시지 출력하고 종료함

5. 각 레벨별로 **게임 순위**를 유지해야 함. 순위는 키보드로 창고지기를 움직인 횟수가 짧을수록 순위가 높고 **5명**을 유지함. 만일 움직인 횟수가 같다면 이전에 플레이한 플레이어가 더 높은 순위를 가짐. `undo`도 움직임에 포함되어야 함. 프로그램이 종료되기 전에 `ranking.txt` 파일에 순위를 저장해야 함 

6. 게임을 중간에 중단하고 다시 시작했으면 움직인 개수를 이어주어야 함 

7. 다음 명령을 지원해야 함 
  * `h` (왼쪽), `j` (아래), `k` (위), `l` (오른쪽) : 창고지기 조정

  * `u` (undo) : 최대 5번 할 수 있음

  * `r` (replay) : 현재 맵을 처음부터 다시 시작(움직임 횟수는 계속 유지)

  * `n` (new) : 첫 번째 맵부터 다시 시작(움직임 횟수 기록 삭제)

  * `e` (exit) : 게임 종료. 종료하기 전 필요한 정보 저장해야 함

  * `s` (save) : 현재 상태 파일에 저장. 파일 이름은 `sokoban`으로 하고 다음에 다시 게임을 연속해서 할 수 있도록 모든 상태 저장해야 함 

  * `f` (file load) : `sokoban` 파일에서 저장된 내용을 읽어 `save` 시점에서부터 이어서 게임하게 함 

  * `d` (display help) : 명령 내용 보여줌

  * `t` (top) : 게임 순위 보여줌. `t` 만 입력하면 전체 순위. `t` 다음 숫자가 오면 해당 맵의 순위
  
8. `map` , `ranking` , `sokoban` 파일은 모두 **텍스트 파일**로 만들어야 함 

9. `cygwin `에서 **컴파일** 되어야 하며 컴파일 오류는 **0점**

10. copy 하면 모두 **0점**

11. 프로젝트 진행은 `GitHub`를 통해서 해야 함 

12. 프로젝트 제출시 **점수표**에 자체 평가 점수를 적어서 제출하고 거짓으로 평가하면 감점함. **참여율**은 참여도에 따라 기입하는데 팀원 참여율의 합은 100이 되도록 해야 함 

13. 팀원이 동등하게 프로젝트에 참여했다면 **개인 점수**는 팀이 받은 점수를 받지만, 불균등하게 참여했 다면 참여율에 따라 다음과 같이 개인 점수가 부여됨

    >점수 = 팀점수 * 참여율 * 팀원수

14. 프로젝트 검사시 **테스트 방법**

```
$ cat testfile khhjjhhhhhkke
$ ./a < testfile
```

15. 예제 화면

```
$ sokoban
Start....
input name : kmh
```

```
	Hello kmh

    #####
    #   #
    #$  #
  ###  $###
  #  $  $ #
### # ### #     ######
#   # ### #######  OO#
# $  $             OO#
##### #### #@####  OO#
    #     ###  ######
    ########
(Command) // t 명령만 enter로 입력받음, 다른 명령은 누름과 동시에 실행.
```

```
	Hello kmh

    #####
    #   #
    #$ $#
  ###   ###
  #       #
### #@### #     ######
#   #$### #######  $$#
#                  OO#
##### #### # ####  O$#
    #     ###  ######
    ########
(Command) h j k l
```

```
	Hello kmh
	
h(왼쪽), j(아래), k(위), l(오른쪽) u(undo)
r(replay)
n(new)
e(exit)
s(save)
f(file load) d(display help) t(top)
(Command) d
```

```
	Hello kmh

map 1
kmh 50
kmh 65
lee 70
(Command) t
```

```
SEE YOU kmh....

(command) e
```



## 평가

| 과목  | 프로그래밍 기초 및 실습 | 팀 프로젝트 | 점 |
| :-----: | :-----------------------: | :-----------: | :------: |
|       | **학번**                | **이름**    | **참여율** |
| 팀원1 | 20192852                | 이강준      |        |
| 팀원2 | 20192860                | 이재호      |        |
| 팀원3 | 20192873                | 정준서      |        |
| 팀원4 | 20192880                | 한도협      |        |



| 평가항목                                    | 구현여부 | 배점 | 평가점수 |
| ------------------------------------------- | :--------: | :----: | :--------: |
| 1. 파일로부터 맵을 정상적으로 읽어들이는가? |          | 5    |          |
|2. 읽어드린 맵의 오류를 처리하는가?||4||
|3. 사용자명을 입력받고 유지하는가?||3||
|4. 모든 맵을 완수한 후 프로그램이 종료되는가?||3||
|5. 순위 처리가 정확히 되는가?||4||
|6. 프로그램이 종료되더라도 순위가 유지되는가?||4||
|7. `h`, `j`, `k`, `l` 키로 이동이 제대로 되는가?||5||
|8. `undo` 기능이 제대로 동작하는가?||8||
|9. `replay` 기능이 제대로 동작하는가?||5||
|10. `new` 기능이 제대로 동작하는가?||5||
|11. `exit` 기능이 제대로 동작하는가?||5||
|12. `save` 기능이 제대로 동작하는가?||4||
|13. `file load` 기능이 제대로 동작하는가?||10||
|14. `display help` 기능이 제대로 동작하는가?||3||
|15. `top` 기능이 제대로 동작하는가?||4||
|16. 맵 별 `top` 기능이 제대로 동작하는가?||4||
|17. 프로그램 코드는 함수별로 설계 되었는가?||8||
|18. `GitHub`를 잘 활용했는가?||8||
|19. 출력물에 주석문, 함수 요약 설명, 역할 분담 명시가 잘 되어 있는가?||8||
|합계||100||

* 팀원들 참여율의 총합이 100%가 되게 명시해야 하며, 각자의 분담 영역을 보고서에 확실히 밝힐 것
* 컴파일 시 오류가 발생하여 실행할 수 없는 경우에는 0점 처리가 됨
* Copy 본으로 판명되면 0점 처리
