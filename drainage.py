def get_value(li, row, column):
    if row < 0 or column < 0:
        return 0
    try:
        return li[row][column]
    except IndexError:
        return 0


n = int(input())
results = {}
for asdf in range(n):
    table = []
    title, rows, columns = input().split()
    rows = int(rows)
    columns = int(columns)

    for r in range(rows):
        table.append([int(x) for x in input().split()])

    flattened = [j for sub in table for j in sub]

    sort = sorted(range(len(flattened)), key=lambda k: flattened[k])

    distance = [[0 for i in range(columns)] for j in range(rows)]
    #print(sort)
    maxdist = 0
    for i in sort:
        r = i//columns
        c = i % columns
        #print(r)
        #print(c)
        w = 1
        x = 1
        y = 1
        z = 1
        if get_value(table, r, c) == get_value(table, r-1, c):
            w = 0
        if get_value(table, r, c) == get_value(table, r+1, c):
            x = 0
        if get_value(table, r, c) == get_value(table, r, c-1):
            y = 0
        if get_value(table, r, c) == get_value(table, r, c+1):
            z = 0
        #print(distance)
        distance[r][c] = max(max(get_value(distance, r-1, c)*w, get_value(distance, r+1, c)*x),
                             max(get_value(distance, r, c-1)*y, get_value(distance, r, c+1)*z)) + 1
        if distance[r][c] > maxdist:
            maxdist = distance[r][c]
    results[title] = maxdist

for key in results:
    print(key + ": " + str(results[key]))    

