def bfs(g, s, e, parent):
    visited = [False] * len(g)
    q = [s]
    visited[s] = True

    while q:
        u = q.pop(0)
        for k in range(len(g[u])):
            if visited[k] is False and g[u][k] > 0:
                q.append(k)
                visited[k] = True
                parent[k] = u
    if visited[e]:
        return True
    else:
        return False


def ff(g, start, end):
    parent = [-1] * (len(g))
    max_flow = 0
    while bfs(g, start, end, parent):
        path_flow = float("Inf")
        s = end
        while s != start:
            path_flow = min(path_flow, g[parent[s]][s])
            s = parent[s]
        max_flow += path_flow
        v = end
        while v != start:
            u = parent[v]
            g[u][v] -= path_flow
            g[v][u] += path_flow
            v = parent[v]
    return max_flow


r, c, n = input().split()

r = int(r)
c = int(c)
n = int(n)

studentclass = {}
classcapacity = {}
ids = {}
graph = []

for i in range(r):
    name, course = input().split()
    if name not in studentclass:
        studentclass[name] = [course]
    else:
        studentclass[name].append(course)

for j in range(c):
    course, capacity = input().split()
    capacity = int(capacity)
    classcapacity[course] = capacity
    if course not in ids:
        ids[j + len(studentclass) + 1] = course
# print(studentclass)
# print(classcapacity)

# print(len(studentclass)+len(classcapacity))
source = [0]*(2+len(studentclass)+len(classcapacity))
for i in range(len(studentclass)):
    source[i+1] = n
graph.append(source)

for name in studentclass:
    row = [0]*(2+len(studentclass)+len(classcapacity))
    for i in range((len(row))):
        # print(i in ids)
        try:
            if ids[i] in studentclass[name]:
                row[i] = 1
        except:
            None

    graph.append(row)

for course in classcapacity:
    row = [0] * (2 + len(studentclass) + len(classcapacity))
    row[len(row)-1] = classcapacity[course]
    graph.append(row)

graph.append([0] * (2 + len(studentclass) + len(classcapacity)))
#print(graph)
maxflow = ff(graph, 0, 1 + len(studentclass) + len(classcapacity))

validenrollment = True
validcapacity = True
for i in range(len(studentclass)):
    # print(graph[1 + i][0])
    if graph[1 + i][0] != n:
        validenrollment = False
count = 1
for course in classcapacity:
    if graph[1 + len(studentclass) + len(classcapacity)][len(studentclass)+count] > classcapacity[course]:
        validcapacity = False
    count += 1


#print("valid enrollemnt: " + str(validenrollment))
#print("valid capacity: " + str(validcapacity))
#print(graph)
#print(maxflow)
#print(len(studentclass)*n)
#print(maxflow == len(studentclass)*n)

if maxflow == len(studentclass)*n: # validcapacity and validenrollment and
    print("Yes")
else:
    print("No")
