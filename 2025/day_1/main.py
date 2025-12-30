start_val = 50
zer_count = 0

direction = ''
rotate = 0

with open("input.txt") as f:
    with open("output.txt", 'w') as w:
        for l in f:
            direction = l[:1]
            rotate = int(l[1:])
            r_count = 0
            if direction == 'L':
                print("before ", start_val, file=w)
                print("rotate val L", rotate, file=w)

                 
                r_count = rotate // 100
                rmdr = rotate % 100

                if(start_val - rmdr < 0 and start_val != 0):
                    r_count += 1

                start_val = (start_val - rmdr) % 100
                
                if(start_val == 0):
                    zer_count += 1
                
                print("after ", start_val, file=w)

                zer_count += r_count
                print("total zero count, ", zer_count, file=w)
                

            elif l[:1] == 'R':
                print("before ", start_val, file=w)
                
                r_count = rotate // 100
                rmdr = rotate % 100

                if(start_val + rmdr > 100):
                    r_count += 1

                start_val = (start_val + rmdr) % 100
                print("rotate val R", rotate, file=w)
                print("after ", start_val, file=w)
             
                if start_val == 0:
                    zer_count += 1

                zer_count += r_count
                print("total zero count, ", zer_count, file=w)
print(start_val)
print(zer_count)