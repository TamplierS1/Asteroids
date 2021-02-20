from glob import glob

#get sources
sources_list = glob("*.cpp")
print(sources_list)

file = open("sources_list.cmake", "w+")

#write to file
file_contents = "target_sources(asteroids PRIVATE "
for source in sources_list:
    file_contents += source + " "
file_contents += ")"

file.write(file_contents)

file.close()
