def count_cuboids_with_same_faces(n, cuboids):
    face_count_map = {}
    
    def get_face_count_key(cuboid):
        face_count = [0, 0, 0, 0, 0, 0]
        for face in cuboid:
            face_count[face - 1] += 1
        return tuple(face_count)
    
    def get_face_pairs(cuboid):
        return [[cuboid[0], cuboid[3]], [cuboid[1], cuboid[5]], [cuboid[2], cuboid[4]]]
    
    for i in range(n):
        cuboid = list(map(int, cuboids[i]))
        face_count_key = get_face_count_key(cuboid)
        face_pairs = get_face_pairs(cuboid)
        
        if face_count_key not in face_count_map:
            face_count_map[face_count_key] = []
        
        face_count_map[face_count_key].append(face_pairs)
    
    def are_same_cuboids(cuboid1, cuboid2):
        for k in range(3):
            if cuboid1[0] == cuboid2[k]:
                temp1 = [cuboid1[1][0], cuboid1[2][0], cuboid1[1][1], cuboid1[2][1]]
                temp2 = [cuboid2[k - 2][0], cuboid2[k - 1][0], cuboid2[k - 2][1], cuboid2[k - 1][1]]
                
                if temp1 == temp2:
                    return True
                
                for l in range(1, 4):
                    if temp1 == temp2[-l:] + temp2[:4 - l]:
                        return True
                
                if cuboid1[0][0] == cuboid1[0][1]:
                    temp2 = [cuboid2[k - 1][1], cuboid2[k - 2][1], cuboid2[k - 1][0], cuboid2[k - 2][0]]
                    if temp1 == temp2:
                        return True
                    for l in range(1, 4):
                        if temp1 == temp2[-l:] + temp2[:4 - l]:
                            return True
            
            elif cuboid1[0] == [cuboid2[k][1], cuboid2[k][0]]:
                temp1 = [cuboid1[1][0], cuboid1[2][0], cuboid1[1][1], cuboid1[2][1]]
                temp2 = [cuboid2[k - 1][1], cuboid2[k - 2][1], cuboid2[k - 1][0], cuboid2[k - 2][0]]
                
                if temp1 == temp2:
                    return True
                
                for l in range(1, 4):
                    if temp1 == temp2[-l:] + temp2[:4 - l]:
                        return True
        
        return False
    
    answer = 0
    
    for key in face_count_map:
        cuboid_group = face_count_map[key]
        n_group = len(cuboid_group)
        
        if n_group == 1:
            answer += 1
            continue
        
        indices = list(range(n_group))
        for i in range(n_group):
            to_remove = []
            for j in range(i + 1, n_group):
                if are_same_cuboids(cuboid_group[i], cuboid_group[j]):
                    to_remove.append(j)
            for index in to_remove:
                if index in indices:
                    indices.remove(index)
        
        answer += len(indices)
    
    return answer

# Example usage
n = int(input())
cuboids = [list(map(int, input().split())) for _ in range(n)]
print(count_cuboids_with_same_faces(n, cuboids))
