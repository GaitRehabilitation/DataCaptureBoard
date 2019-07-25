import struct
import csv
import io
import sys
import os

if(len(sys.argv) != 2): 
    print("python ./decode.py <file_to_decode>")
    sys.exit(0)
file_path = str(sys.argv[1])
filename = os.path.basename(file_path)

with open(filename, "rb") as file:
    header_size = struct.unpack('h',io.BytesIO(file.read(2)).read())[0]
    print(header_size)
    header_data = struct.unpack('=4cbI10c',io.BytesIO(file.read(header_size)).read())
    # header_data = struct.unpack('I',io.BytesIO(file.read(4)).read())
    
    print(header_data)
    # with open(filename.split('.')[0] + ".csv",'w') as csvfile:
        # writer = csv.DictWriter(csvfile, fieldnames=['time','accx','accy','accz','gyrox','gyroy','gyroz','temp'])
        # writer.writeheader()


        # while(1):
        #     data_block = file.read(512)
        #     if data_block == b'':
        #         break
        #     bt = io.BytesIO(data_block)
        #     count = struct.unpack('h',bt.read(2))
        #     if(count == 0):
        #         break
        #     overruns = struct.unpack('h',bt.read(2))
        #     for i in range(1,count[0]):
        #         data = struct.unpack('Ihhhhhhh',bt.read(18))
        #         print(data)
        #         writer.writerow({
        #         'time':data[0],
        #         'accx':data[1],
        #         'accy':data[2],
        #         'accz':data[3],
        #         'gyrox':data[4],
        #         'gyroy':data[5],
        #         'gyroz':data[6],
        #         'temp':data[7]})