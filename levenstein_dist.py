def levensten_dist(str_1, str_2):
    len_str1 = len(str_1)
    len_str2 = len(str_2)
    if min(len_str1, len_str2) <= 0:
        return max(len_str1, len_str2)
    else:
        if str_1[len_str1 - 1] == str_2[len_str2 - 1]:
            i = 0
        else:
            i = 1   
        return min(levensten_dist(str_1[:-1], str_2) + 1,
                   levensten_dist(str_1, str_2[:-1]) + 1,
                   levensten_dist(str_1[:-1], str_2[:-1]) + i)
