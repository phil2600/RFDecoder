require 'socket'

time = Time.new
time = Time.now

clientSession = TCPSocket.new( "192.168.1.2", 1337)
puts "[+]       Starting Connection"
clientSession.write("Client connected")

@@number_of_temp = 0
@@sensors_temp = Hash.new
@@hum = 0

@@last_sensor_name = ""

@@run_weekly = 0
@@run_monthly = 0

def     update_rrd()
        @@number_of_temp = 0
        @@sensors_temp.each do|name, temp|
                puts "#{name}: #{temp}"
        end
        `rrdtool update tempDB.rrd N:#{@@sensors_temp["THN132N-AC"]}:#{@@sensors_temp["THN132N-5E"]}:#{@@sensors_temp["THGR810-55"]}`
        puts @@hum
        `rrdtool update hygDB.rrd N:#{@@hum}`


        `sh graphs.sh`

        @@run_weekly+=1
        @@run_monthly+=1
        if @@run_weekly == 5
                `sh graphs_weekly.sh`
                @@run_weekly = 0
        end

        if @@run_monthly == 10
                `sh graphs_monthly.sh`
                @@run_monthly = 0
        end

        @@sensors_temp = Hash.new
end

while line = clientSession.gets
         sensor_name, id, channel, temp, battery, hum = line.split(";")
		 # OLD hack to change ... sensor_name+ID compliance ... for rrdtools
		#puts "channel : #{channel}" 
		sensor_name_id = "THN132N-5E" if channel == "4"
		sensor_name_id = "THN132N-AC" if channel == "2"
		sensor_name_id = "THGR810-55" if channel == "9"
		#puts "name : #{sensor_name_id}"
		 # \OLD hack
        if !@@sensors_temp.has_key?(sensor_name_id) && @@last_sensor_name != sensor_name_id
                #puts "[+] ADD: #{@@number_of_temp} - [#{sensor_name_id}] ch#{channel} - #{temp}c H#{hum}"
                @@hum = hum if hum
                 @@sensors_temp[sensor_name_id] = temp
                @@number_of_temp+=1
         end
        update_rrd if @@number_of_temp == 3
         @@last_sensor_name = sensor_name_id
        #sleep (1)
 end

