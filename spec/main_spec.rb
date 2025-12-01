describe 'database' do

  def run_script(commands)
    raw_output = nil

    IO.popen("./build/sqlmini", "r+") do |pipe|
      commands.each do |cmd|
        pipe.puts cmd
      end

      pipe.close_write

      raw_output = pipe.gets(nil)
    end
    
  raw_output.split("\n")
  end

  it 'inserts and retrieves a row' do
    result = run_script([
      "insert 1 user1 person1@example.com",
      "select",
      ".exit",
    ])

    expect(result).to match_array([
      "db > Executed.",
      "db > |  00000001  |  user1            |  person1@example.com  |",
      "Executed.",
      "db > ",
    ])
  end

  it 'prints error message when table is full' do
    script = (1..1401).map do |i|
      "insert #{i} user#{i} person#{i}@example.com"
    end

    script << ".exit"
    result = run_script(script)
    expect(result[-2]).to eq("db > Error: Table full.")
  end

  it 'allow inserting of strings tha are the maximum length' do
    long_username = "a" * 32
    long_email = "a" * 255
    script = [
      "insert 1 #{long_username} #{long_email}",
      "select",
      ".exit",
    ]

    result = run_script(script)
    expect(result).to match_array([
        "db > Executed.",
        "db > |  00000001  |  #{long_username}  |  #{long_email}  |",
        "Executed.",
        "db > ",
    ])
  end

  it 'prints error message if strings are too long' do
    too_long_username = "a" * 33
    too_long_email = "a" * 256
    script = [
      "insert 1 #{too_long_username} #{too_long_email}",
      "select",
      ".exit",
    ]

    result = run_script(script)
    expect(result).to match_array([
        "db > String is too long.",
        "db > Executed.",
        "db > ",
    ])
  end

  it 'prints an error message if id is negative' do
    script = [
      "insert -1 name foo@bar.com",
      "select",
      ".exit",
    ]

    result = run_script(script)
    expect(result).to match_array([
        "db > ID must be positive.",
        "db > Executed.",
        "db > ",
    ])
  end

  it 'keeps data after closing connection' do

    r0 = run_script([
      "insert 1 user1 user1@example.com",
      ".exit",
    ])

    expect(r0).to match_array([
        "db > Executed.",
        "db > ",
    ])

    r1 = run_script([
      "select",
      ".exit",
    ])

    expect(r1).to match_array([
        "db > |  00000001  |  user1            |  user1@example.com  |",
        "Executed.",
        "db > ",
    ])
  end

end
