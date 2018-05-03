Minimize
 maxTime + co1o7Finish - co1o7Start + co2o8Finish - co2o8Start + co3o9Finish - co3o9Start + co4o10Finish - co4o10Start + co5o11Finish - co5o11Start + co6o12Finish - co6o12Start
SUBJECT TO
o1Finish - o1Start >= 40
o2Finish - o2Start >= 40
o3Finish - o3Start >= 40
o4Finish - o4Start >= 40
o5Finish - o5Start >= 40
o6Finish - o6Start >= 40
o7Finish - o7Start >= 70
o8Finish - o8Start >= 70
o9Finish - o9Start >= 70
o10Finish - o10Start >= 70
o11Finish - o11Start >= 70
o12Finish - o12Start >= 70
o1Inj - o1Start <= 0
o1Ej - o1Finish >= 0
o2Inj - o2Start <= 0
o2Ej - o2Finish >= 0
o3Inj - o3Start <= 0
o3Ej - o3Finish >= 0
o4Inj - o4Start <= 0
o4Ej - o4Finish >= 0
o5Inj - o5Start <= 0
o5Ej - o5Finish >= 0
o6Inj - o6Start <= 0
o6Ej - o6Finish >= 0
o7Inj - o7Start <= 0
o7Ej - o7Finish >= 0
o8Inj - o8Start <= 0
o8Ej - o8Finish >= 0
o9Inj - o9Start <= 0
o9Ej - o9Finish >= 0
o10Inj - o10Start <= 0
o10Ej - o10Finish >= 0
o11Inj - o11Start <= 0
o11Ej - o11Finish >= 0
o12Inj - o12Start <= 0
o12Ej - o12Finish >= 0
co1o7Start - o1Finish >= 0
o7Start - co1o7Finish >= 0
o7Inj - co1o7Finish <= -10
o1Ej - co1o7Start >= 10
co2o8Start - o2Finish >= 0
o8Start - co2o8Finish >= 0
o8Inj - co2o8Finish <= -10
o2Ej - co2o8Start >= 10
co3o9Start - o3Finish >= 0
o9Start - co3o9Finish >= 0
o9Inj - co3o9Finish <= -10
o3Ej - co3o9Start >= 10
co4o10Start - o4Finish >= 0
o10Start - co4o10Finish >= 0
o10Inj - co4o10Finish <= -10
o4Ej - co4o10Start >= 10
co5o11Start - o5Finish >= 0
o11Start - co5o11Finish >= 0
o11Inj - co5o11Finish <= -10
o5Ej - co5o11Start >= 10
co6o12Start - o6Finish >= 0
o12Start - co6o12Finish >= 0
o12Inj - co6o12Finish <= -10
o6Ej - co6o12Start >= 10
co1o7SESd1 - 10000 o1Bindd1 - 10000 o7Bindd1 <= 0
co1o7SESd1 + 10000 o1Bindd1 + 10000 o7Bindd1 >= 0
co1o7SESd1 - o1Bindd1 >= 0
co1o7SESd1 - o7Bindd1 >= 0
co1o7SESd2 - 10000 o1Bindd2 - 10000 o7Bindd2 <= 0
co1o7SESd2 + 10000 o1Bindd2 + 10000 o7Bindd2 >= 0
co1o7SESd2 - o1Bindd2 >= 0
co1o7SESd2 - o7Bindd2 >= 0
co1o7SESd3 - 10000 o1Bindd3 - 10000 o7Bindd3 <= 0
co1o7SESd3 + 10000 o1Bindd3 + 10000 o7Bindd3 >= 0
co1o7SESd3 - o1Bindd3 >= 0
co1o7SESd3 - o7Bindd3 >= 0
co1o7SESd4 - 10000 o1Bindd4 - 10000 o7Bindd4 <= 0
co1o7SESd4 + 10000 o1Bindd4 + 10000 o7Bindd4 >= 0
co1o7SESd4 - o1Bindd4 >= 0
co1o7SESd4 - o7Bindd4 >= 0
co1o7SESd5 - 10000 o1Bindd5 - 10000 o7Bindd5 <= 0
co1o7SESd5 + 10000 o1Bindd5 + 10000 o7Bindd5 >= 0
co1o7SESd5 - o1Bindd5 >= 0
co1o7SESd5 - o7Bindd5 >= 0
co1o7SES - co1o7SESd1 <= 0
co1o7SES - co1o7SESd2 <= 0
co1o7SES - co1o7SESd3 <= 0
co1o7SES - co1o7SESd4 <= 0
co1o7SES - co1o7SESd5 <= 0
co1o7SES - 10000 co1o7SESd1 - 10000 co1o7SESd2 - 10000 co1o7SESd3 - 10000 co1o7SESd4 - 10000 co1o7SESd5 >= -49999
co1o7SES + 10000 co1o7SESd1 + 10000 co1o7SESd2 + 10000 co1o7SESd3 + 10000 co1o7SESd4 + 10000 co1o7SESd5 <= 50001
co1o7Finish - co1o7Start - 10000 co1o7SES <= 0
co1o7Finish - co1o7Start + 10000 co1o7SES >= 0
co1o7Finish - co1o7Start - 10000 co1o7SES >= -9990
co2o8SESd1 - 10000 o2Bindd1 - 10000 o8Bindd1 <= 0
co2o8SESd1 + 10000 o2Bindd1 + 10000 o8Bindd1 >= 0
co2o8SESd1 - o2Bindd1 >= 0
co2o8SESd1 - o8Bindd1 >= 0
co2o8SESd2 - 10000 o2Bindd2 - 10000 o8Bindd2 <= 0
co2o8SESd2 + 10000 o2Bindd2 + 10000 o8Bindd2 >= 0
co2o8SESd2 - o2Bindd2 >= 0
co2o8SESd2 - o8Bindd2 >= 0
co2o8SESd3 - 10000 o2Bindd3 - 10000 o8Bindd3 <= 0
co2o8SESd3 + 10000 o2Bindd3 + 10000 o8Bindd3 >= 0
co2o8SESd3 - o2Bindd3 >= 0
co2o8SESd3 - o8Bindd3 >= 0
co2o8SESd4 - 10000 o2Bindd4 - 10000 o8Bindd4 <= 0
co2o8SESd4 + 10000 o2Bindd4 + 10000 o8Bindd4 >= 0
co2o8SESd4 - o2Bindd4 >= 0
co2o8SESd4 - o8Bindd4 >= 0
co2o8SESd5 - 10000 o2Bindd5 - 10000 o8Bindd5 <= 0
co2o8SESd5 + 10000 o2Bindd5 + 10000 o8Bindd5 >= 0
co2o8SESd5 - o2Bindd5 >= 0
co2o8SESd5 - o8Bindd5 >= 0
co2o8SES - co2o8SESd1 <= 0
co2o8SES - co2o8SESd2 <= 0
co2o8SES - co2o8SESd3 <= 0
co2o8SES - co2o8SESd4 <= 0
co2o8SES - co2o8SESd5 <= 0
co2o8SES - 10000 co2o8SESd1 - 10000 co2o8SESd2 - 10000 co2o8SESd3 - 10000 co2o8SESd4 - 10000 co2o8SESd5 >= -49999
co2o8SES + 10000 co2o8SESd1 + 10000 co2o8SESd2 + 10000 co2o8SESd3 + 10000 co2o8SESd4 + 10000 co2o8SESd5 <= 50001
co2o8Finish - co2o8Start - 10000 co2o8SES <= 0
co2o8Finish - co2o8Start + 10000 co2o8SES >= 0
co2o8Finish - co2o8Start - 10000 co2o8SES >= -9990
co3o9SESd1 - 10000 o3Bindd1 - 10000 o9Bindd1 <= 0
co3o9SESd1 + 10000 o3Bindd1 + 10000 o9Bindd1 >= 0
co3o9SESd1 - o3Bindd1 >= 0
co3o9SESd1 - o9Bindd1 >= 0
co3o9SESd2 - 10000 o3Bindd2 - 10000 o9Bindd2 <= 0
co3o9SESd2 + 10000 o3Bindd2 + 10000 o9Bindd2 >= 0
co3o9SESd2 - o3Bindd2 >= 0
co3o9SESd2 - o9Bindd2 >= 0
co3o9SESd3 - 10000 o3Bindd3 - 10000 o9Bindd3 <= 0
co3o9SESd3 + 10000 o3Bindd3 + 10000 o9Bindd3 >= 0
co3o9SESd3 - o3Bindd3 >= 0
co3o9SESd3 - o9Bindd3 >= 0
co3o9SESd4 - 10000 o3Bindd4 - 10000 o9Bindd4 <= 0
co3o9SESd4 + 10000 o3Bindd4 + 10000 o9Bindd4 >= 0
co3o9SESd4 - o3Bindd4 >= 0
co3o9SESd4 - o9Bindd4 >= 0
co3o9SESd5 - 10000 o3Bindd5 - 10000 o9Bindd5 <= 0
co3o9SESd5 + 10000 o3Bindd5 + 10000 o9Bindd5 >= 0
co3o9SESd5 - o3Bindd5 >= 0
co3o9SESd5 - o9Bindd5 >= 0
co3o9SES - co3o9SESd1 <= 0
co3o9SES - co3o9SESd2 <= 0
co3o9SES - co3o9SESd3 <= 0
co3o9SES - co3o9SESd4 <= 0
co3o9SES - co3o9SESd5 <= 0
co3o9SES - 10000 co3o9SESd1 - 10000 co3o9SESd2 - 10000 co3o9SESd3 - 10000 co3o9SESd4 - 10000 co3o9SESd5 >= -49999
co3o9SES + 10000 co3o9SESd1 + 10000 co3o9SESd2 + 10000 co3o9SESd3 + 10000 co3o9SESd4 + 10000 co3o9SESd5 <= 50001
co3o9Finish - co3o9Start - 10000 co3o9SES <= 0
co3o9Finish - co3o9Start + 10000 co3o9SES >= 0
co3o9Finish - co3o9Start - 10000 co3o9SES >= -9990
co4o10SESd1 - 10000 o4Bindd1 - 10000 o10Bindd1 <= 0
co4o10SESd1 + 10000 o4Bindd1 + 10000 o10Bindd1 >= 0
co4o10SESd1 - o4Bindd1 >= 0
co4o10SESd1 - o10Bindd1 >= 0
co4o10SESd2 - 10000 o4Bindd2 - 10000 o10Bindd2 <= 0
co4o10SESd2 + 10000 o4Bindd2 + 10000 o10Bindd2 >= 0
co4o10SESd2 - o4Bindd2 >= 0
co4o10SESd2 - o10Bindd2 >= 0
co4o10SESd3 - 10000 o4Bindd3 - 10000 o10Bindd3 <= 0
co4o10SESd3 + 10000 o4Bindd3 + 10000 o10Bindd3 >= 0
co4o10SESd3 - o4Bindd3 >= 0
co4o10SESd3 - o10Bindd3 >= 0
co4o10SESd4 - 10000 o4Bindd4 - 10000 o10Bindd4 <= 0
co4o10SESd4 + 10000 o4Bindd4 + 10000 o10Bindd4 >= 0
co4o10SESd4 - o4Bindd4 >= 0
co4o10SESd4 - o10Bindd4 >= 0
co4o10SESd5 - 10000 o4Bindd5 - 10000 o10Bindd5 <= 0
co4o10SESd5 + 10000 o4Bindd5 + 10000 o10Bindd5 >= 0
co4o10SESd5 - o4Bindd5 >= 0
co4o10SESd5 - o10Bindd5 >= 0
co4o10SES - co4o10SESd1 <= 0
co4o10SES - co4o10SESd2 <= 0
co4o10SES - co4o10SESd3 <= 0
co4o10SES - co4o10SESd4 <= 0
co4o10SES - co4o10SESd5 <= 0
co4o10SES - 10000 co4o10SESd1 - 10000 co4o10SESd2 - 10000 co4o10SESd3 - 10000 co4o10SESd4 - 10000 co4o10SESd5 >= -49999
co4o10SES + 10000 co4o10SESd1 + 10000 co4o10SESd2 + 10000 co4o10SESd3 + 10000 co4o10SESd4 + 10000 co4o10SESd5 <= 50001
co4o10Finish - co4o10Start - 10000 co4o10SES <= 0
co4o10Finish - co4o10Start + 10000 co4o10SES >= 0
co4o10Finish - co4o10Start - 10000 co4o10SES >= -9990
co5o11SESd1 - 10000 o5Bindd1 - 10000 o11Bindd1 <= 0
co5o11SESd1 + 10000 o5Bindd1 + 10000 o11Bindd1 >= 0
co5o11SESd1 - o5Bindd1 >= 0
co5o11SESd1 - o11Bindd1 >= 0
co5o11SESd2 - 10000 o5Bindd2 - 10000 o11Bindd2 <= 0
co5o11SESd2 + 10000 o5Bindd2 + 10000 o11Bindd2 >= 0
co5o11SESd2 - o5Bindd2 >= 0
co5o11SESd2 - o11Bindd2 >= 0
co5o11SESd3 - 10000 o5Bindd3 - 10000 o11Bindd3 <= 0
co5o11SESd3 + 10000 o5Bindd3 + 10000 o11Bindd3 >= 0
co5o11SESd3 - o5Bindd3 >= 0
co5o11SESd3 - o11Bindd3 >= 0
co5o11SESd4 - 10000 o5Bindd4 - 10000 o11Bindd4 <= 0
co5o11SESd4 + 10000 o5Bindd4 + 10000 o11Bindd4 >= 0
co5o11SESd4 - o5Bindd4 >= 0
co5o11SESd4 - o11Bindd4 >= 0
co5o11SESd5 - 10000 o5Bindd5 - 10000 o11Bindd5 <= 0
co5o11SESd5 + 10000 o5Bindd5 + 10000 o11Bindd5 >= 0
co5o11SESd5 - o5Bindd5 >= 0
co5o11SESd5 - o11Bindd5 >= 0
co5o11SES - co5o11SESd1 <= 0
co5o11SES - co5o11SESd2 <= 0
co5o11SES - co5o11SESd3 <= 0
co5o11SES - co5o11SESd4 <= 0
co5o11SES - co5o11SESd5 <= 0
co5o11SES - 10000 co5o11SESd1 - 10000 co5o11SESd2 - 10000 co5o11SESd3 - 10000 co5o11SESd4 - 10000 co5o11SESd5 >= -49999
co5o11SES + 10000 co5o11SESd1 + 10000 co5o11SESd2 + 10000 co5o11SESd3 + 10000 co5o11SESd4 + 10000 co5o11SESd5 <= 50001
co5o11Finish - co5o11Start - 10000 co5o11SES <= 0
co5o11Finish - co5o11Start + 10000 co5o11SES >= 0
co5o11Finish - co5o11Start - 10000 co5o11SES >= -9990
co6o12SESd1 - 10000 o6Bindd1 - 10000 o12Bindd1 <= 0
co6o12SESd1 + 10000 o6Bindd1 + 10000 o12Bindd1 >= 0
co6o12SESd1 - o6Bindd1 >= 0
co6o12SESd1 - o12Bindd1 >= 0
co6o12SESd2 - 10000 o6Bindd2 - 10000 o12Bindd2 <= 0
co6o12SESd2 + 10000 o6Bindd2 + 10000 o12Bindd2 >= 0
co6o12SESd2 - o6Bindd2 >= 0
co6o12SESd2 - o12Bindd2 >= 0
co6o12SESd3 - 10000 o6Bindd3 - 10000 o12Bindd3 <= 0
co6o12SESd3 + 10000 o6Bindd3 + 10000 o12Bindd3 >= 0
co6o12SESd3 - o6Bindd3 >= 0
co6o12SESd3 - o12Bindd3 >= 0
co6o12SESd4 - 10000 o6Bindd4 - 10000 o12Bindd4 <= 0
co6o12SESd4 + 10000 o6Bindd4 + 10000 o12Bindd4 >= 0
co6o12SESd4 - o6Bindd4 >= 0
co6o12SESd4 - o12Bindd4 >= 0
co6o12SESd5 - 10000 o6Bindd5 - 10000 o12Bindd5 <= 0
co6o12SESd5 + 10000 o6Bindd5 + 10000 o12Bindd5 >= 0
co6o12SESd5 - o6Bindd5 >= 0
co6o12SESd5 - o12Bindd5 >= 0
co6o12SES - co6o12SESd1 <= 0
co6o12SES - co6o12SESd2 <= 0
co6o12SES - co6o12SESd3 <= 0
co6o12SES - co6o12SESd4 <= 0
co6o12SES - co6o12SESd5 <= 0
co6o12SES - 10000 co6o12SESd1 - 10000 co6o12SESd2 - 10000 co6o12SESd3 - 10000 co6o12SESd4 - 10000 co6o12SESd5 >= -49999
co6o12SES + 10000 co6o12SESd1 + 10000 co6o12SESd2 + 10000 co6o12SESd3 + 10000 co6o12SESd4 + 10000 co6o12SESd5 <= 50001
co6o12Finish - co6o12Start - 10000 co6o12SES <= 0
co6o12Finish - co6o12Start + 10000 co6o12SES >= 0
co6o12Finish - co6o12Start - 10000 co6o12SES >= -9990
o1Bindd4 = 1
o1Bindd5 = 1
 + o1Bindd1 + o1Bindd2 + o1Bindd3 + o1Bindd4 + o1Bindd5 = 4
o2Bindd4 = 1
o2Bindd5 = 1
 + o2Bindd1 + o2Bindd2 + o2Bindd3 + o2Bindd4 + o2Bindd5 = 4
o3Bindd4 = 1
o3Bindd5 = 1
 + o3Bindd1 + o3Bindd2 + o3Bindd3 + o3Bindd4 + o3Bindd5 = 4
o4Bindd4 = 1
o4Bindd5 = 1
 + o4Bindd1 + o4Bindd2 + o4Bindd3 + o4Bindd4 + o4Bindd5 = 4
o5Bindd4 = 1
o5Bindd5 = 1
 + o5Bindd1 + o5Bindd2 + o5Bindd3 + o5Bindd4 + o5Bindd5 = 4
o6Bindd4 = 1
o6Bindd5 = 1
 + o6Bindd1 + o6Bindd2 + o6Bindd3 + o6Bindd4 + o6Bindd5 = 4
o7Bindd1 = 1
o7Bindd2 = 1
o7Bindd3 = 1
 + o7Bindd1 + o7Bindd2 + o7Bindd3 + o7Bindd4 + o7Bindd5 = 4
o8Bindd1 = 1
o8Bindd2 = 1
o8Bindd3 = 1
 + o8Bindd1 + o8Bindd2 + o8Bindd3 + o8Bindd4 + o8Bindd5 = 4
o9Bindd1 = 1
o9Bindd2 = 1
o9Bindd3 = 1
 + o9Bindd1 + o9Bindd2 + o9Bindd3 + o9Bindd4 + o9Bindd5 = 4
o10Bindd1 = 1
o10Bindd2 = 1
o10Bindd3 = 1
 + o10Bindd1 + o10Bindd2 + o10Bindd3 + o10Bindd4 + o10Bindd5 = 4
o11Bindd1 = 1
o11Bindd2 = 1
o11Bindd3 = 1
 + o11Bindd1 + o11Bindd2 + o11Bindd3 + o11Bindd4 + o11Bindd5 = 4
o12Bindd1 = 1
o12Bindd2 = 1
o12Bindd3 = 1
 + o12Bindd1 + o12Bindd2 + o12Bindd3 + o12Bindd4 + o12Bindd5 = 4
o1Inj - o2Ej + 10000 o2Beforeo1 >= 0
o2Inj - o1Ej + 10000 o1Beforeo2 >= 0
 - o2Bindd1 - o1Bindd1 + o2Beforeo1 + o1Beforeo2 <= 1
o1Inj - o3Ej + 10000 o3Beforeo1 >= 0
o3Inj - o1Ej + 10000 o1Beforeo3 >= 0
 - o3Bindd1 - o1Bindd1 + o3Beforeo1 + o1Beforeo3 <= 1
o2Inj - o3Ej + 10000 o3Beforeo2 >= 0
o3Inj - o2Ej + 10000 o2Beforeo3 >= 0
 - o3Bindd1 - o2Bindd1 + o3Beforeo2 + o2Beforeo3 <= 1
o1Inj - o4Ej + 10000 o4Beforeo1 >= 0
o4Inj - o1Ej + 10000 o1Beforeo4 >= 0
 - o4Bindd1 - o1Bindd1 + o4Beforeo1 + o1Beforeo4 <= 1
o2Inj - o4Ej + 10000 o4Beforeo2 >= 0
o4Inj - o2Ej + 10000 o2Beforeo4 >= 0
 - o4Bindd1 - o2Bindd1 + o4Beforeo2 + o2Beforeo4 <= 1
o3Inj - o4Ej + 10000 o4Beforeo3 >= 0
o4Inj - o3Ej + 10000 o3Beforeo4 >= 0
 - o4Bindd1 - o3Bindd1 + o4Beforeo3 + o3Beforeo4 <= 1
o1Inj - o5Ej + 10000 o5Beforeo1 >= 0
o5Inj - o1Ej + 10000 o1Beforeo5 >= 0
 - o5Bindd1 - o1Bindd1 + o5Beforeo1 + o1Beforeo5 <= 1
o2Inj - o5Ej + 10000 o5Beforeo2 >= 0
o5Inj - o2Ej + 10000 o2Beforeo5 >= 0
 - o5Bindd1 - o2Bindd1 + o5Beforeo2 + o2Beforeo5 <= 1
o3Inj - o5Ej + 10000 o5Beforeo3 >= 0
o5Inj - o3Ej + 10000 o3Beforeo5 >= 0
 - o5Bindd1 - o3Bindd1 + o5Beforeo3 + o3Beforeo5 <= 1
o4Inj - o5Ej + 10000 o5Beforeo4 >= 0
o5Inj - o4Ej + 10000 o4Beforeo5 >= 0
 - o5Bindd1 - o4Bindd1 + o5Beforeo4 + o4Beforeo5 <= 1
o1Inj - o6Ej + 10000 o6Beforeo1 >= 0
o6Inj - o1Ej + 10000 o1Beforeo6 >= 0
 - o6Bindd1 - o1Bindd1 + o6Beforeo1 + o1Beforeo6 <= 1
o2Inj - o6Ej + 10000 o6Beforeo2 >= 0
o6Inj - o2Ej + 10000 o2Beforeo6 >= 0
 - o6Bindd1 - o2Bindd1 + o6Beforeo2 + o2Beforeo6 <= 1
o3Inj - o6Ej + 10000 o6Beforeo3 >= 0
o6Inj - o3Ej + 10000 o3Beforeo6 >= 0
 - o6Bindd1 - o3Bindd1 + o6Beforeo3 + o3Beforeo6 <= 1
o4Inj - o6Ej + 10000 o6Beforeo4 >= 0
o6Inj - o4Ej + 10000 o4Beforeo6 >= 0
 - o6Bindd1 - o4Bindd1 + o6Beforeo4 + o4Beforeo6 <= 1
o5Inj - o6Ej + 10000 o6Beforeo5 >= 0
o6Inj - o5Ej + 10000 o5Beforeo6 >= 0
 - o6Bindd1 - o5Bindd1 + o6Beforeo5 + o5Beforeo6 <= 1
o7Inj - o8Ej + 10000 o8Beforeo7 >= 0
o8Inj - o7Ej + 10000 o7Beforeo8 >= 0
 - o8Bindd1 - o7Bindd1 + o8Beforeo7 + o7Beforeo8 <= 1
o7Inj - o9Ej + 10000 o9Beforeo7 >= 0
o9Inj - o7Ej + 10000 o7Beforeo9 >= 0
 - o9Bindd1 - o7Bindd1 + o9Beforeo7 + o7Beforeo9 <= 1
o8Inj - o9Ej + 10000 o9Beforeo8 >= 0
o9Inj - o8Ej + 10000 o8Beforeo9 >= 0
 - o9Bindd1 - o8Bindd1 + o9Beforeo8 + o8Beforeo9 <= 1
o7Inj - o10Ej + 10000 o10Beforeo7 >= 0
o10Inj - o7Ej + 10000 o7Beforeo10 >= 0
 - o10Bindd1 - o7Bindd1 + o10Beforeo7 + o7Beforeo10 <= 1
o8Inj - o10Ej + 10000 o10Beforeo8 >= 0
o10Inj - o8Ej + 10000 o8Beforeo10 >= 0
 - o10Bindd1 - o8Bindd1 + o10Beforeo8 + o8Beforeo10 <= 1
o9Inj - o10Ej + 10000 o10Beforeo9 >= 0
o10Inj - o9Ej + 10000 o9Beforeo10 >= 0
 - o10Bindd1 - o9Bindd1 + o10Beforeo9 + o9Beforeo10 <= 1
o7Inj - o11Ej + 10000 o11Beforeo7 >= 0
o11Inj - o7Ej + 10000 o7Beforeo11 >= 0
 - o11Bindd1 - o7Bindd1 + o11Beforeo7 + o7Beforeo11 <= 1
o8Inj - o11Ej + 10000 o11Beforeo8 >= 0
o11Inj - o8Ej + 10000 o8Beforeo11 >= 0
 - o11Bindd1 - o8Bindd1 + o11Beforeo8 + o8Beforeo11 <= 1
o9Inj - o11Ej + 10000 o11Beforeo9 >= 0
o11Inj - o9Ej + 10000 o9Beforeo11 >= 0
 - o11Bindd1 - o9Bindd1 + o11Beforeo9 + o9Beforeo11 <= 1
o10Inj - o11Ej + 10000 o11Beforeo10 >= 0
o11Inj - o10Ej + 10000 o10Beforeo11 >= 0
 - o11Bindd1 - o10Bindd1 + o11Beforeo10 + o10Beforeo11 <= 1
o7Inj - o12Ej + 10000 o12Beforeo7 >= 0
o12Inj - o7Ej + 10000 o7Beforeo12 >= 0
 - o12Bindd1 - o7Bindd1 + o12Beforeo7 + o7Beforeo12 <= 1
o8Inj - o12Ej + 10000 o12Beforeo8 >= 0
o12Inj - o8Ej + 10000 o8Beforeo12 >= 0
 - o12Bindd1 - o8Bindd1 + o12Beforeo8 + o8Beforeo12 <= 1
o9Inj - o12Ej + 10000 o12Beforeo9 >= 0
o12Inj - o9Ej + 10000 o9Beforeo12 >= 0
 - o12Bindd1 - o9Bindd1 + o12Beforeo9 + o9Beforeo12 <= 1
o10Inj - o12Ej + 10000 o12Beforeo10 >= 0
o12Inj - o10Ej + 10000 o10Beforeo12 >= 0
 - o12Bindd1 - o10Bindd1 + o12Beforeo10 + o10Beforeo12 <= 1
o11Inj - o12Ej + 10000 o12Beforeo11 >= 0
o12Inj - o11Ej + 10000 o11Beforeo12 >= 0
 - o12Bindd1 - o11Bindd1 + o12Beforeo11 + o11Beforeo12 <= 1
o1Inj - o2Ej + 10000 o2Beforeo1 >= 0
o2Inj - o1Ej + 10000 o1Beforeo2 >= 0
 - o2Bindd2 - o1Bindd2 + o2Beforeo1 + o1Beforeo2 <= 1
o1Inj - o3Ej + 10000 o3Beforeo1 >= 0
o3Inj - o1Ej + 10000 o1Beforeo3 >= 0
 - o3Bindd2 - o1Bindd2 + o3Beforeo1 + o1Beforeo3 <= 1
o2Inj - o3Ej + 10000 o3Beforeo2 >= 0
o3Inj - o2Ej + 10000 o2Beforeo3 >= 0
 - o3Bindd2 - o2Bindd2 + o3Beforeo2 + o2Beforeo3 <= 1
o1Inj - o4Ej + 10000 o4Beforeo1 >= 0
o4Inj - o1Ej + 10000 o1Beforeo4 >= 0
 - o4Bindd2 - o1Bindd2 + o4Beforeo1 + o1Beforeo4 <= 1
o2Inj - o4Ej + 10000 o4Beforeo2 >= 0
o4Inj - o2Ej + 10000 o2Beforeo4 >= 0
 - o4Bindd2 - o2Bindd2 + o4Beforeo2 + o2Beforeo4 <= 1
o3Inj - o4Ej + 10000 o4Beforeo3 >= 0
o4Inj - o3Ej + 10000 o3Beforeo4 >= 0
 - o4Bindd2 - o3Bindd2 + o4Beforeo3 + o3Beforeo4 <= 1
o1Inj - o5Ej + 10000 o5Beforeo1 >= 0
o5Inj - o1Ej + 10000 o1Beforeo5 >= 0
 - o5Bindd2 - o1Bindd2 + o5Beforeo1 + o1Beforeo5 <= 1
o2Inj - o5Ej + 10000 o5Beforeo2 >= 0
o5Inj - o2Ej + 10000 o2Beforeo5 >= 0
 - o5Bindd2 - o2Bindd2 + o5Beforeo2 + o2Beforeo5 <= 1
o3Inj - o5Ej + 10000 o5Beforeo3 >= 0
o5Inj - o3Ej + 10000 o3Beforeo5 >= 0
 - o5Bindd2 - o3Bindd2 + o5Beforeo3 + o3Beforeo5 <= 1
o4Inj - o5Ej + 10000 o5Beforeo4 >= 0
o5Inj - o4Ej + 10000 o4Beforeo5 >= 0
 - o5Bindd2 - o4Bindd2 + o5Beforeo4 + o4Beforeo5 <= 1
o1Inj - o6Ej + 10000 o6Beforeo1 >= 0
o6Inj - o1Ej + 10000 o1Beforeo6 >= 0
 - o6Bindd2 - o1Bindd2 + o6Beforeo1 + o1Beforeo6 <= 1
o2Inj - o6Ej + 10000 o6Beforeo2 >= 0
o6Inj - o2Ej + 10000 o2Beforeo6 >= 0
 - o6Bindd2 - o2Bindd2 + o6Beforeo2 + o2Beforeo6 <= 1
o3Inj - o6Ej + 10000 o6Beforeo3 >= 0
o6Inj - o3Ej + 10000 o3Beforeo6 >= 0
 - o6Bindd2 - o3Bindd2 + o6Beforeo3 + o3Beforeo6 <= 1
o4Inj - o6Ej + 10000 o6Beforeo4 >= 0
o6Inj - o4Ej + 10000 o4Beforeo6 >= 0
 - o6Bindd2 - o4Bindd2 + o6Beforeo4 + o4Beforeo6 <= 1
o5Inj - o6Ej + 10000 o6Beforeo5 >= 0
o6Inj - o5Ej + 10000 o5Beforeo6 >= 0
 - o6Bindd2 - o5Bindd2 + o6Beforeo5 + o5Beforeo6 <= 1
o7Inj - o8Ej + 10000 o8Beforeo7 >= 0
o8Inj - o7Ej + 10000 o7Beforeo8 >= 0
 - o8Bindd2 - o7Bindd2 + o8Beforeo7 + o7Beforeo8 <= 1
o7Inj - o9Ej + 10000 o9Beforeo7 >= 0
o9Inj - o7Ej + 10000 o7Beforeo9 >= 0
 - o9Bindd2 - o7Bindd2 + o9Beforeo7 + o7Beforeo9 <= 1
o8Inj - o9Ej + 10000 o9Beforeo8 >= 0
o9Inj - o8Ej + 10000 o8Beforeo9 >= 0
 - o9Bindd2 - o8Bindd2 + o9Beforeo8 + o8Beforeo9 <= 1
o7Inj - o10Ej + 10000 o10Beforeo7 >= 0
o10Inj - o7Ej + 10000 o7Beforeo10 >= 0
 - o10Bindd2 - o7Bindd2 + o10Beforeo7 + o7Beforeo10 <= 1
o8Inj - o10Ej + 10000 o10Beforeo8 >= 0
o10Inj - o8Ej + 10000 o8Beforeo10 >= 0
 - o10Bindd2 - o8Bindd2 + o10Beforeo8 + o8Beforeo10 <= 1
o9Inj - o10Ej + 10000 o10Beforeo9 >= 0
o10Inj - o9Ej + 10000 o9Beforeo10 >= 0
 - o10Bindd2 - o9Bindd2 + o10Beforeo9 + o9Beforeo10 <= 1
o7Inj - o11Ej + 10000 o11Beforeo7 >= 0
o11Inj - o7Ej + 10000 o7Beforeo11 >= 0
 - o11Bindd2 - o7Bindd2 + o11Beforeo7 + o7Beforeo11 <= 1
o8Inj - o11Ej + 10000 o11Beforeo8 >= 0
o11Inj - o8Ej + 10000 o8Beforeo11 >= 0
 - o11Bindd2 - o8Bindd2 + o11Beforeo8 + o8Beforeo11 <= 1
o9Inj - o11Ej + 10000 o11Beforeo9 >= 0
o11Inj - o9Ej + 10000 o9Beforeo11 >= 0
 - o11Bindd2 - o9Bindd2 + o11Beforeo9 + o9Beforeo11 <= 1
o10Inj - o11Ej + 10000 o11Beforeo10 >= 0
o11Inj - o10Ej + 10000 o10Beforeo11 >= 0
 - o11Bindd2 - o10Bindd2 + o11Beforeo10 + o10Beforeo11 <= 1
o7Inj - o12Ej + 10000 o12Beforeo7 >= 0
o12Inj - o7Ej + 10000 o7Beforeo12 >= 0
 - o12Bindd2 - o7Bindd2 + o12Beforeo7 + o7Beforeo12 <= 1
o8Inj - o12Ej + 10000 o12Beforeo8 >= 0
o12Inj - o8Ej + 10000 o8Beforeo12 >= 0
 - o12Bindd2 - o8Bindd2 + o12Beforeo8 + o8Beforeo12 <= 1
o9Inj - o12Ej + 10000 o12Beforeo9 >= 0
o12Inj - o9Ej + 10000 o9Beforeo12 >= 0
 - o12Bindd2 - o9Bindd2 + o12Beforeo9 + o9Beforeo12 <= 1
o10Inj - o12Ej + 10000 o12Beforeo10 >= 0
o12Inj - o10Ej + 10000 o10Beforeo12 >= 0
 - o12Bindd2 - o10Bindd2 + o12Beforeo10 + o10Beforeo12 <= 1
o11Inj - o12Ej + 10000 o12Beforeo11 >= 0
o12Inj - o11Ej + 10000 o11Beforeo12 >= 0
 - o12Bindd2 - o11Bindd2 + o12Beforeo11 + o11Beforeo12 <= 1
o1Inj - o2Ej + 10000 o2Beforeo1 >= 0
o2Inj - o1Ej + 10000 o1Beforeo2 >= 0
 - o2Bindd3 - o1Bindd3 + o2Beforeo1 + o1Beforeo2 <= 1
o1Inj - o3Ej + 10000 o3Beforeo1 >= 0
o3Inj - o1Ej + 10000 o1Beforeo3 >= 0
 - o3Bindd3 - o1Bindd3 + o3Beforeo1 + o1Beforeo3 <= 1
o2Inj - o3Ej + 10000 o3Beforeo2 >= 0
o3Inj - o2Ej + 10000 o2Beforeo3 >= 0
 - o3Bindd3 - o2Bindd3 + o3Beforeo2 + o2Beforeo3 <= 1
o1Inj - o4Ej + 10000 o4Beforeo1 >= 0
o4Inj - o1Ej + 10000 o1Beforeo4 >= 0
 - o4Bindd3 - o1Bindd3 + o4Beforeo1 + o1Beforeo4 <= 1
o2Inj - o4Ej + 10000 o4Beforeo2 >= 0
o4Inj - o2Ej + 10000 o2Beforeo4 >= 0
 - o4Bindd3 - o2Bindd3 + o4Beforeo2 + o2Beforeo4 <= 1
o3Inj - o4Ej + 10000 o4Beforeo3 >= 0
o4Inj - o3Ej + 10000 o3Beforeo4 >= 0
 - o4Bindd3 - o3Bindd3 + o4Beforeo3 + o3Beforeo4 <= 1
o1Inj - o5Ej + 10000 o5Beforeo1 >= 0
o5Inj - o1Ej + 10000 o1Beforeo5 >= 0
 - o5Bindd3 - o1Bindd3 + o5Beforeo1 + o1Beforeo5 <= 1
o2Inj - o5Ej + 10000 o5Beforeo2 >= 0
o5Inj - o2Ej + 10000 o2Beforeo5 >= 0
 - o5Bindd3 - o2Bindd3 + o5Beforeo2 + o2Beforeo5 <= 1
o3Inj - o5Ej + 10000 o5Beforeo3 >= 0
o5Inj - o3Ej + 10000 o3Beforeo5 >= 0
 - o5Bindd3 - o3Bindd3 + o5Beforeo3 + o3Beforeo5 <= 1
o4Inj - o5Ej + 10000 o5Beforeo4 >= 0
o5Inj - o4Ej + 10000 o4Beforeo5 >= 0
 - o5Bindd3 - o4Bindd3 + o5Beforeo4 + o4Beforeo5 <= 1
o1Inj - o6Ej + 10000 o6Beforeo1 >= 0
o6Inj - o1Ej + 10000 o1Beforeo6 >= 0
 - o6Bindd3 - o1Bindd3 + o6Beforeo1 + o1Beforeo6 <= 1
o2Inj - o6Ej + 10000 o6Beforeo2 >= 0
o6Inj - o2Ej + 10000 o2Beforeo6 >= 0
 - o6Bindd3 - o2Bindd3 + o6Beforeo2 + o2Beforeo6 <= 1
o3Inj - o6Ej + 10000 o6Beforeo3 >= 0
o6Inj - o3Ej + 10000 o3Beforeo6 >= 0
 - o6Bindd3 - o3Bindd3 + o6Beforeo3 + o3Beforeo6 <= 1
o4Inj - o6Ej + 10000 o6Beforeo4 >= 0
o6Inj - o4Ej + 10000 o4Beforeo6 >= 0
 - o6Bindd3 - o4Bindd3 + o6Beforeo4 + o4Beforeo6 <= 1
o5Inj - o6Ej + 10000 o6Beforeo5 >= 0
o6Inj - o5Ej + 10000 o5Beforeo6 >= 0
 - o6Bindd3 - o5Bindd3 + o6Beforeo5 + o5Beforeo6 <= 1
o7Inj - o8Ej + 10000 o8Beforeo7 >= 0
o8Inj - o7Ej + 10000 o7Beforeo8 >= 0
 - o8Bindd3 - o7Bindd3 + o8Beforeo7 + o7Beforeo8 <= 1
o7Inj - o9Ej + 10000 o9Beforeo7 >= 0
o9Inj - o7Ej + 10000 o7Beforeo9 >= 0
 - o9Bindd3 - o7Bindd3 + o9Beforeo7 + o7Beforeo9 <= 1
o8Inj - o9Ej + 10000 o9Beforeo8 >= 0
o9Inj - o8Ej + 10000 o8Beforeo9 >= 0
 - o9Bindd3 - o8Bindd3 + o9Beforeo8 + o8Beforeo9 <= 1
o7Inj - o10Ej + 10000 o10Beforeo7 >= 0
o10Inj - o7Ej + 10000 o7Beforeo10 >= 0
 - o10Bindd3 - o7Bindd3 + o10Beforeo7 + o7Beforeo10 <= 1
o8Inj - o10Ej + 10000 o10Beforeo8 >= 0
o10Inj - o8Ej + 10000 o8Beforeo10 >= 0
 - o10Bindd3 - o8Bindd3 + o10Beforeo8 + o8Beforeo10 <= 1
o9Inj - o10Ej + 10000 o10Beforeo9 >= 0
o10Inj - o9Ej + 10000 o9Beforeo10 >= 0
 - o10Bindd3 - o9Bindd3 + o10Beforeo9 + o9Beforeo10 <= 1
o7Inj - o11Ej + 10000 o11Beforeo7 >= 0
o11Inj - o7Ej + 10000 o7Beforeo11 >= 0
 - o11Bindd3 - o7Bindd3 + o11Beforeo7 + o7Beforeo11 <= 1
o8Inj - o11Ej + 10000 o11Beforeo8 >= 0
o11Inj - o8Ej + 10000 o8Beforeo11 >= 0
 - o11Bindd3 - o8Bindd3 + o11Beforeo8 + o8Beforeo11 <= 1
o9Inj - o11Ej + 10000 o11Beforeo9 >= 0
o11Inj - o9Ej + 10000 o9Beforeo11 >= 0
 - o11Bindd3 - o9Bindd3 + o11Beforeo9 + o9Beforeo11 <= 1
o10Inj - o11Ej + 10000 o11Beforeo10 >= 0
o11Inj - o10Ej + 10000 o10Beforeo11 >= 0
 - o11Bindd3 - o10Bindd3 + o11Beforeo10 + o10Beforeo11 <= 1
o7Inj - o12Ej + 10000 o12Beforeo7 >= 0
o12Inj - o7Ej + 10000 o7Beforeo12 >= 0
 - o12Bindd3 - o7Bindd3 + o12Beforeo7 + o7Beforeo12 <= 1
o8Inj - o12Ej + 10000 o12Beforeo8 >= 0
o12Inj - o8Ej + 10000 o8Beforeo12 >= 0
 - o12Bindd3 - o8Bindd3 + o12Beforeo8 + o8Beforeo12 <= 1
o9Inj - o12Ej + 10000 o12Beforeo9 >= 0
o12Inj - o9Ej + 10000 o9Beforeo12 >= 0
 - o12Bindd3 - o9Bindd3 + o12Beforeo9 + o9Beforeo12 <= 1
o10Inj - o12Ej + 10000 o12Beforeo10 >= 0
o12Inj - o10Ej + 10000 o10Beforeo12 >= 0
 - o12Bindd3 - o10Bindd3 + o12Beforeo10 + o10Beforeo12 <= 1
o11Inj - o12Ej + 10000 o12Beforeo11 >= 0
o12Inj - o11Ej + 10000 o11Beforeo12 >= 0
 - o12Bindd3 - o11Bindd3 + o12Beforeo11 + o11Beforeo12 <= 1
o1Inj - o2Ej + 10000 o2Beforeo1 >= 0
o2Inj - o1Ej + 10000 o1Beforeo2 >= 0
 - o2Bindd4 - o1Bindd4 + o2Beforeo1 + o1Beforeo2 <= 1
o1Inj - o3Ej + 10000 o3Beforeo1 >= 0
o3Inj - o1Ej + 10000 o1Beforeo3 >= 0
 - o3Bindd4 - o1Bindd4 + o3Beforeo1 + o1Beforeo3 <= 1
o2Inj - o3Ej + 10000 o3Beforeo2 >= 0
o3Inj - o2Ej + 10000 o2Beforeo3 >= 0
 - o3Bindd4 - o2Bindd4 + o3Beforeo2 + o2Beforeo3 <= 1
o1Inj - o4Ej + 10000 o4Beforeo1 >= 0
o4Inj - o1Ej + 10000 o1Beforeo4 >= 0
 - o4Bindd4 - o1Bindd4 + o4Beforeo1 + o1Beforeo4 <= 1
o2Inj - o4Ej + 10000 o4Beforeo2 >= 0
o4Inj - o2Ej + 10000 o2Beforeo4 >= 0
 - o4Bindd4 - o2Bindd4 + o4Beforeo2 + o2Beforeo4 <= 1
o3Inj - o4Ej + 10000 o4Beforeo3 >= 0
o4Inj - o3Ej + 10000 o3Beforeo4 >= 0
 - o4Bindd4 - o3Bindd4 + o4Beforeo3 + o3Beforeo4 <= 1
o1Inj - o5Ej + 10000 o5Beforeo1 >= 0
o5Inj - o1Ej + 10000 o1Beforeo5 >= 0
 - o5Bindd4 - o1Bindd4 + o5Beforeo1 + o1Beforeo5 <= 1
o2Inj - o5Ej + 10000 o5Beforeo2 >= 0
o5Inj - o2Ej + 10000 o2Beforeo5 >= 0
 - o5Bindd4 - o2Bindd4 + o5Beforeo2 + o2Beforeo5 <= 1
o3Inj - o5Ej + 10000 o5Beforeo3 >= 0
o5Inj - o3Ej + 10000 o3Beforeo5 >= 0
 - o5Bindd4 - o3Bindd4 + o5Beforeo3 + o3Beforeo5 <= 1
o4Inj - o5Ej + 10000 o5Beforeo4 >= 0
o5Inj - o4Ej + 10000 o4Beforeo5 >= 0
 - o5Bindd4 - o4Bindd4 + o5Beforeo4 + o4Beforeo5 <= 1
o1Inj - o6Ej + 10000 o6Beforeo1 >= 0
o6Inj - o1Ej + 10000 o1Beforeo6 >= 0
 - o6Bindd4 - o1Bindd4 + o6Beforeo1 + o1Beforeo6 <= 1
o2Inj - o6Ej + 10000 o6Beforeo2 >= 0
o6Inj - o2Ej + 10000 o2Beforeo6 >= 0
 - o6Bindd4 - o2Bindd4 + o6Beforeo2 + o2Beforeo6 <= 1
o3Inj - o6Ej + 10000 o6Beforeo3 >= 0
o6Inj - o3Ej + 10000 o3Beforeo6 >= 0
 - o6Bindd4 - o3Bindd4 + o6Beforeo3 + o3Beforeo6 <= 1
o4Inj - o6Ej + 10000 o6Beforeo4 >= 0
o6Inj - o4Ej + 10000 o4Beforeo6 >= 0
 - o6Bindd4 - o4Bindd4 + o6Beforeo4 + o4Beforeo6 <= 1
o5Inj - o6Ej + 10000 o6Beforeo5 >= 0
o6Inj - o5Ej + 10000 o5Beforeo6 >= 0
 - o6Bindd4 - o5Bindd4 + o6Beforeo5 + o5Beforeo6 <= 1
o7Inj - o8Ej + 10000 o8Beforeo7 >= 0
o8Inj - o7Ej + 10000 o7Beforeo8 >= 0
 - o8Bindd4 - o7Bindd4 + o8Beforeo7 + o7Beforeo8 <= 1
o7Inj - o9Ej + 10000 o9Beforeo7 >= 0
o9Inj - o7Ej + 10000 o7Beforeo9 >= 0
 - o9Bindd4 - o7Bindd4 + o9Beforeo7 + o7Beforeo9 <= 1
o8Inj - o9Ej + 10000 o9Beforeo8 >= 0
o9Inj - o8Ej + 10000 o8Beforeo9 >= 0
 - o9Bindd4 - o8Bindd4 + o9Beforeo8 + o8Beforeo9 <= 1
o7Inj - o10Ej + 10000 o10Beforeo7 >= 0
o10Inj - o7Ej + 10000 o7Beforeo10 >= 0
 - o10Bindd4 - o7Bindd4 + o10Beforeo7 + o7Beforeo10 <= 1
o8Inj - o10Ej + 10000 o10Beforeo8 >= 0
o10Inj - o8Ej + 10000 o8Beforeo10 >= 0
 - o10Bindd4 - o8Bindd4 + o10Beforeo8 + o8Beforeo10 <= 1
o9Inj - o10Ej + 10000 o10Beforeo9 >= 0
o10Inj - o9Ej + 10000 o9Beforeo10 >= 0
 - o10Bindd4 - o9Bindd4 + o10Beforeo9 + o9Beforeo10 <= 1
o7Inj - o11Ej + 10000 o11Beforeo7 >= 0
o11Inj - o7Ej + 10000 o7Beforeo11 >= 0
 - o11Bindd4 - o7Bindd4 + o11Beforeo7 + o7Beforeo11 <= 1
o8Inj - o11Ej + 10000 o11Beforeo8 >= 0
o11Inj - o8Ej + 10000 o8Beforeo11 >= 0
 - o11Bindd4 - o8Bindd4 + o11Beforeo8 + o8Beforeo11 <= 1
o9Inj - o11Ej + 10000 o11Beforeo9 >= 0
o11Inj - o9Ej + 10000 o9Beforeo11 >= 0
 - o11Bindd4 - o9Bindd4 + o11Beforeo9 + o9Beforeo11 <= 1
o10Inj - o11Ej + 10000 o11Beforeo10 >= 0
o11Inj - o10Ej + 10000 o10Beforeo11 >= 0
 - o11Bindd4 - o10Bindd4 + o11Beforeo10 + o10Beforeo11 <= 1
o7Inj - o12Ej + 10000 o12Beforeo7 >= 0
o12Inj - o7Ej + 10000 o7Beforeo12 >= 0
 - o12Bindd4 - o7Bindd4 + o12Beforeo7 + o7Beforeo12 <= 1
o8Inj - o12Ej + 10000 o12Beforeo8 >= 0
o12Inj - o8Ej + 10000 o8Beforeo12 >= 0
 - o12Bindd4 - o8Bindd4 + o12Beforeo8 + o8Beforeo12 <= 1
o9Inj - o12Ej + 10000 o12Beforeo9 >= 0
o12Inj - o9Ej + 10000 o9Beforeo12 >= 0
 - o12Bindd4 - o9Bindd4 + o12Beforeo9 + o9Beforeo12 <= 1
o10Inj - o12Ej + 10000 o12Beforeo10 >= 0
o12Inj - o10Ej + 10000 o10Beforeo12 >= 0
 - o12Bindd4 - o10Bindd4 + o12Beforeo10 + o10Beforeo12 <= 1
o11Inj - o12Ej + 10000 o12Beforeo11 >= 0
o12Inj - o11Ej + 10000 o11Beforeo12 >= 0
 - o12Bindd4 - o11Bindd4 + o12Beforeo11 + o11Beforeo12 <= 1
o1Inj - o2Ej + 10000 o2Beforeo1 >= 0
o2Inj - o1Ej + 10000 o1Beforeo2 >= 0
 - o2Bindd5 - o1Bindd5 + o2Beforeo1 + o1Beforeo2 <= 1
o1Inj - o3Ej + 10000 o3Beforeo1 >= 0
o3Inj - o1Ej + 10000 o1Beforeo3 >= 0
 - o3Bindd5 - o1Bindd5 + o3Beforeo1 + o1Beforeo3 <= 1
o2Inj - o3Ej + 10000 o3Beforeo2 >= 0
o3Inj - o2Ej + 10000 o2Beforeo3 >= 0
 - o3Bindd5 - o2Bindd5 + o3Beforeo2 + o2Beforeo3 <= 1
o1Inj - o4Ej + 10000 o4Beforeo1 >= 0
o4Inj - o1Ej + 10000 o1Beforeo4 >= 0
 - o4Bindd5 - o1Bindd5 + o4Beforeo1 + o1Beforeo4 <= 1
o2Inj - o4Ej + 10000 o4Beforeo2 >= 0
o4Inj - o2Ej + 10000 o2Beforeo4 >= 0
 - o4Bindd5 - o2Bindd5 + o4Beforeo2 + o2Beforeo4 <= 1
o3Inj - o4Ej + 10000 o4Beforeo3 >= 0
o4Inj - o3Ej + 10000 o3Beforeo4 >= 0
 - o4Bindd5 - o3Bindd5 + o4Beforeo3 + o3Beforeo4 <= 1
o1Inj - o5Ej + 10000 o5Beforeo1 >= 0
o5Inj - o1Ej + 10000 o1Beforeo5 >= 0
 - o5Bindd5 - o1Bindd5 + o5Beforeo1 + o1Beforeo5 <= 1
o2Inj - o5Ej + 10000 o5Beforeo2 >= 0
o5Inj - o2Ej + 10000 o2Beforeo5 >= 0
 - o5Bindd5 - o2Bindd5 + o5Beforeo2 + o2Beforeo5 <= 1
o3Inj - o5Ej + 10000 o5Beforeo3 >= 0
o5Inj - o3Ej + 10000 o3Beforeo5 >= 0
 - o5Bindd5 - o3Bindd5 + o5Beforeo3 + o3Beforeo5 <= 1
o4Inj - o5Ej + 10000 o5Beforeo4 >= 0
o5Inj - o4Ej + 10000 o4Beforeo5 >= 0
 - o5Bindd5 - o4Bindd5 + o5Beforeo4 + o4Beforeo5 <= 1
o1Inj - o6Ej + 10000 o6Beforeo1 >= 0
o6Inj - o1Ej + 10000 o1Beforeo6 >= 0
 - o6Bindd5 - o1Bindd5 + o6Beforeo1 + o1Beforeo6 <= 1
o2Inj - o6Ej + 10000 o6Beforeo2 >= 0
o6Inj - o2Ej + 10000 o2Beforeo6 >= 0
 - o6Bindd5 - o2Bindd5 + o6Beforeo2 + o2Beforeo6 <= 1
o3Inj - o6Ej + 10000 o6Beforeo3 >= 0
o6Inj - o3Ej + 10000 o3Beforeo6 >= 0
 - o6Bindd5 - o3Bindd5 + o6Beforeo3 + o3Beforeo6 <= 1
o4Inj - o6Ej + 10000 o6Beforeo4 >= 0
o6Inj - o4Ej + 10000 o4Beforeo6 >= 0
 - o6Bindd5 - o4Bindd5 + o6Beforeo4 + o4Beforeo6 <= 1
o5Inj - o6Ej + 10000 o6Beforeo5 >= 0
o6Inj - o5Ej + 10000 o5Beforeo6 >= 0
 - o6Bindd5 - o5Bindd5 + o6Beforeo5 + o5Beforeo6 <= 1
o7Inj - o8Ej + 10000 o8Beforeo7 >= 0
o8Inj - o7Ej + 10000 o7Beforeo8 >= 0
 - o8Bindd5 - o7Bindd5 + o8Beforeo7 + o7Beforeo8 <= 1
o7Inj - o9Ej + 10000 o9Beforeo7 >= 0
o9Inj - o7Ej + 10000 o7Beforeo9 >= 0
 - o9Bindd5 - o7Bindd5 + o9Beforeo7 + o7Beforeo9 <= 1
o8Inj - o9Ej + 10000 o9Beforeo8 >= 0
o9Inj - o8Ej + 10000 o8Beforeo9 >= 0
 - o9Bindd5 - o8Bindd5 + o9Beforeo8 + o8Beforeo9 <= 1
o7Inj - o10Ej + 10000 o10Beforeo7 >= 0
o10Inj - o7Ej + 10000 o7Beforeo10 >= 0
 - o10Bindd5 - o7Bindd5 + o10Beforeo7 + o7Beforeo10 <= 1
o8Inj - o10Ej + 10000 o10Beforeo8 >= 0
o10Inj - o8Ej + 10000 o8Beforeo10 >= 0
 - o10Bindd5 - o8Bindd5 + o10Beforeo8 + o8Beforeo10 <= 1
o9Inj - o10Ej + 10000 o10Beforeo9 >= 0
o10Inj - o9Ej + 10000 o9Beforeo10 >= 0
 - o10Bindd5 - o9Bindd5 + o10Beforeo9 + o9Beforeo10 <= 1
o7Inj - o11Ej + 10000 o11Beforeo7 >= 0
o11Inj - o7Ej + 10000 o7Beforeo11 >= 0
 - o11Bindd5 - o7Bindd5 + o11Beforeo7 + o7Beforeo11 <= 1
o8Inj - o11Ej + 10000 o11Beforeo8 >= 0
o11Inj - o8Ej + 10000 o8Beforeo11 >= 0
 - o11Bindd5 - o8Bindd5 + o11Beforeo8 + o8Beforeo11 <= 1
o9Inj - o11Ej + 10000 o11Beforeo9 >= 0
o11Inj - o9Ej + 10000 o9Beforeo11 >= 0
 - o11Bindd5 - o9Bindd5 + o11Beforeo9 + o9Beforeo11 <= 1
o10Inj - o11Ej + 10000 o11Beforeo10 >= 0
o11Inj - o10Ej + 10000 o10Beforeo11 >= 0
 - o11Bindd5 - o10Bindd5 + o11Beforeo10 + o10Beforeo11 <= 1
o7Inj - o12Ej + 10000 o12Beforeo7 >= 0
o12Inj - o7Ej + 10000 o7Beforeo12 >= 0
 - o12Bindd5 - o7Bindd5 + o12Beforeo7 + o7Beforeo12 <= 1
o8Inj - o12Ej + 10000 o12Beforeo8 >= 0
o12Inj - o8Ej + 10000 o8Beforeo12 >= 0
 - o12Bindd5 - o8Bindd5 + o12Beforeo8 + o8Beforeo12 <= 1
o9Inj - o12Ej + 10000 o12Beforeo9 >= 0
o12Inj - o9Ej + 10000 o9Beforeo12 >= 0
 - o12Bindd5 - o9Bindd5 + o12Beforeo9 + o9Beforeo12 <= 1
o10Inj - o12Ej + 10000 o12Beforeo10 >= 0
o12Inj - o10Ej + 10000 o10Beforeo12 >= 0
 - o12Bindd5 - o10Bindd5 + o12Beforeo10 + o10Beforeo12 <= 1
o11Inj - o12Ej + 10000 o12Beforeo11 >= 0
o12Inj - o11Ej + 10000 o11Beforeo12 >= 0
 - o12Bindd5 - o11Bindd5 + o12Beforeo11 + o11Beforeo12 <= 1
maxTime - o1Finish >= 0
maxTime - o2Finish >= 0
maxTime - o3Finish >= 0
maxTime - o4Finish >= 0
maxTime - o5Finish >= 0
maxTime - o6Finish >= 0
maxTime - o7Finish >= 0
maxTime - o8Finish >= 0
maxTime - o9Finish >= 0
maxTime - o10Finish >= 0
maxTime - o11Finish >= 0
maxTime - o12Finish >= 0
Binaries
o1Bindd1
o1Bindd2
o1Bindd3
o1Bindd4
o1Bindd5
o2Bindd1
o2Bindd2
o2Bindd3
o2Bindd4
o2Bindd5
o3Bindd1
o3Bindd2
o3Bindd3
o3Bindd4
o3Bindd5
o4Bindd1
o4Bindd2
o4Bindd3
o4Bindd4
o4Bindd5
o5Bindd1
o5Bindd2
o5Bindd3
o5Bindd4
o5Bindd5
o6Bindd1
o6Bindd2
o6Bindd3
o6Bindd4
o6Bindd5
o7Bindd1
o7Bindd2
o7Bindd3
o7Bindd4
o7Bindd5
o8Bindd1
o8Bindd2
o8Bindd3
o8Bindd4
o8Bindd5
o9Bindd1
o9Bindd2
o9Bindd3
o9Bindd4
o9Bindd5
o10Bindd1
o10Bindd2
o10Bindd3
o10Bindd4
o10Bindd5
o11Bindd1
o11Bindd2
o11Bindd3
o11Bindd4
o11Bindd5
o12Bindd1
o12Bindd2
o12Bindd3
o12Bindd4
o12Bindd5
co1o7SES
co1o7SESd1
co1o7SESd2
co1o7SESd3
co1o7SESd4
co1o7SESd5
co2o8SES
co2o8SESd1
co2o8SESd2
co2o8SESd3
co2o8SESd4
co2o8SESd5
co3o9SES
co3o9SESd1
co3o9SESd2
co3o9SESd3
co3o9SESd4
co3o9SESd5
co4o10SES
co4o10SESd1
co4o10SESd2
co4o10SESd3
co4o10SESd4
co4o10SESd5
co5o11SES
co5o11SESd1
co5o11SESd2
co5o11SESd3
co5o11SESd4
co5o11SESd5
co6o12SES
co6o12SESd1
co6o12SESd2
co6o12SESd3
co6o12SESd4
co6o12SESd5
o2Beforeo1
o1Beforeo2
o3Beforeo1
o1Beforeo3
o3Beforeo2
o2Beforeo3
o4Beforeo1
o1Beforeo4
o4Beforeo2
o2Beforeo4
o4Beforeo3
o3Beforeo4
o5Beforeo1
o1Beforeo5
o5Beforeo2
o2Beforeo5
o5Beforeo3
o3Beforeo5
o5Beforeo4
o4Beforeo5
o6Beforeo1
o1Beforeo6
o6Beforeo2
o2Beforeo6
o6Beforeo3
o3Beforeo6
o6Beforeo4
o4Beforeo6
o6Beforeo5
o5Beforeo6
o8Beforeo7
o7Beforeo8
o9Beforeo7
o7Beforeo9
o9Beforeo8
o8Beforeo9
o10Beforeo7
o7Beforeo10
o10Beforeo8
o8Beforeo10
o10Beforeo9
o9Beforeo10
o11Beforeo7
o7Beforeo11
o11Beforeo8
o8Beforeo11
o11Beforeo9
o9Beforeo11
o11Beforeo10
o10Beforeo11
o12Beforeo7
o7Beforeo12
o12Beforeo8
o8Beforeo12
o12Beforeo9
o9Beforeo12
o12Beforeo10
o10Beforeo12
o12Beforeo11
o11Beforeo12
o2Beforeo1
o1Beforeo2
o3Beforeo1
o1Beforeo3
o3Beforeo2
o2Beforeo3
o4Beforeo1
o1Beforeo4
o4Beforeo2
o2Beforeo4
o4Beforeo3
o3Beforeo4
o5Beforeo1
o1Beforeo5
o5Beforeo2
o2Beforeo5
o5Beforeo3
o3Beforeo5
o5Beforeo4
o4Beforeo5
o6Beforeo1
o1Beforeo6
o6Beforeo2
o2Beforeo6
o6Beforeo3
o3Beforeo6
o6Beforeo4
o4Beforeo6
o6Beforeo5
o5Beforeo6
o8Beforeo7
o7Beforeo8
o9Beforeo7
o7Beforeo9
o9Beforeo8
o8Beforeo9
o10Beforeo7
o7Beforeo10
o10Beforeo8
o8Beforeo10
o10Beforeo9
o9Beforeo10
o11Beforeo7
o7Beforeo11
o11Beforeo8
o8Beforeo11
o11Beforeo9
o9Beforeo11
o11Beforeo10
o10Beforeo11
o12Beforeo7
o7Beforeo12
o12Beforeo8
o8Beforeo12
o12Beforeo9
o9Beforeo12
o12Beforeo10
o10Beforeo12
o12Beforeo11
o11Beforeo12
o2Beforeo1
o1Beforeo2
o3Beforeo1
o1Beforeo3
o3Beforeo2
o2Beforeo3
o4Beforeo1
o1Beforeo4
o4Beforeo2
o2Beforeo4
o4Beforeo3
o3Beforeo4
o5Beforeo1
o1Beforeo5
o5Beforeo2
o2Beforeo5
o5Beforeo3
o3Beforeo5
o5Beforeo4
o4Beforeo5
o6Beforeo1
o1Beforeo6
o6Beforeo2
o2Beforeo6
o6Beforeo3
o3Beforeo6
o6Beforeo4
o4Beforeo6
o6Beforeo5
o5Beforeo6
o8Beforeo7
o7Beforeo8
o9Beforeo7
o7Beforeo9
o9Beforeo8
o8Beforeo9
o10Beforeo7
o7Beforeo10
o10Beforeo8
o8Beforeo10
o10Beforeo9
o9Beforeo10
o11Beforeo7
o7Beforeo11
o11Beforeo8
o8Beforeo11
o11Beforeo9
o9Beforeo11
o11Beforeo10
o10Beforeo11
o12Beforeo7
o7Beforeo12
o12Beforeo8
o8Beforeo12
o12Beforeo9
o9Beforeo12
o12Beforeo10
o10Beforeo12
o12Beforeo11
o11Beforeo12
o2Beforeo1
o1Beforeo2
o3Beforeo1
o1Beforeo3
o3Beforeo2
o2Beforeo3
o4Beforeo1
o1Beforeo4
o4Beforeo2
o2Beforeo4
o4Beforeo3
o3Beforeo4
o5Beforeo1
o1Beforeo5
o5Beforeo2
o2Beforeo5
o5Beforeo3
o3Beforeo5
o5Beforeo4
o4Beforeo5
o6Beforeo1
o1Beforeo6
o6Beforeo2
o2Beforeo6
o6Beforeo3
o3Beforeo6
o6Beforeo4
o4Beforeo6
o6Beforeo5
o5Beforeo6
o8Beforeo7
o7Beforeo8
o9Beforeo7
o7Beforeo9
o9Beforeo8
o8Beforeo9
o10Beforeo7
o7Beforeo10
o10Beforeo8
o8Beforeo10
o10Beforeo9
o9Beforeo10
o11Beforeo7
o7Beforeo11
o11Beforeo8
o8Beforeo11
o11Beforeo9
o9Beforeo11
o11Beforeo10
o10Beforeo11
o12Beforeo7
o7Beforeo12
o12Beforeo8
o8Beforeo12
o12Beforeo9
o9Beforeo12
o12Beforeo10
o10Beforeo12
o12Beforeo11
o11Beforeo12
o2Beforeo1
o1Beforeo2
o3Beforeo1
o1Beforeo3
o3Beforeo2
o2Beforeo3
o4Beforeo1
o1Beforeo4
o4Beforeo2
o2Beforeo4
o4Beforeo3
o3Beforeo4
o5Beforeo1
o1Beforeo5
o5Beforeo2
o2Beforeo5
o5Beforeo3
o3Beforeo5
o5Beforeo4
o4Beforeo5
o6Beforeo1
o1Beforeo6
o6Beforeo2
o2Beforeo6
o6Beforeo3
o3Beforeo6
o6Beforeo4
o4Beforeo6
o6Beforeo5
o5Beforeo6
o8Beforeo7
o7Beforeo8
o9Beforeo7
o7Beforeo9
o9Beforeo8
o8Beforeo9
o10Beforeo7
o7Beforeo10
o10Beforeo8
o8Beforeo10
o10Beforeo9
o9Beforeo10
o11Beforeo7
o7Beforeo11
o11Beforeo8
o8Beforeo11
o11Beforeo9
o9Beforeo11
o11Beforeo10
o10Beforeo11
o12Beforeo7
o7Beforeo12
o12Beforeo8
o8Beforeo12
o12Beforeo9
o9Beforeo12
o12Beforeo10
o10Beforeo12
o12Beforeo11
o11Beforeo12
Semi
o1Start
o1Finish
o1Inj
o1Ej
o2Start
o2Finish
o2Inj
o2Ej
o3Start
o3Finish
o3Inj
o3Ej
o4Start
o4Finish
o4Inj
o4Ej
o5Start
o5Finish
o5Inj
o5Ej
o6Start
o6Finish
o6Inj
o6Ej
o7Start
o7Finish
o7Inj
o7Ej
o8Start
o8Finish
o8Inj
o8Ej
o9Start
o9Finish
o9Inj
o9Ej
o10Start
o10Finish
o10Inj
o10Ej
o11Start
o11Finish
o11Inj
o11Ej
o12Start
o12Finish
o12Inj
o12Ej
co1o7Start
co1o7Finish
co2o8Start
co2o8Finish
co3o9Start
co3o9Finish
co4o10Start
co4o10Finish
co5o11Start
co5o11Finish
co6o12Start
co6o12Finish
maxTime
