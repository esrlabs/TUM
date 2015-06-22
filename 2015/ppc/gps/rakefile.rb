
desc "run unittests"
task :runTests do
  sh "bake -b UnitTest -a black --include_filter run"
end
task :default => :run

