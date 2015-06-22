
desc "build"
task :build do
  sh "bake -m gps -b UnitTest -a black"
end

desc "run"
task :run => :build do
  sh "./gps/UnitTest/gpsTests.exe"
end

desc "clean"
task :clean do
  sh "bake -m gps -b UnitTest -a black -c"
end
