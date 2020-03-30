$:.push('gen-rb')
$:.unshift '../../lib/rb/lib'

require 'thrift'

require 'calculadora'

begin
  
    transport = Thrift::BufferedTransport.new(Thrift::Socket.new('localhost', 9090))
    protocol = Thrift::BinaryProtocol.new(transport)
    client = Calculadora::Client.new(protocol)
  
    transport.open()

    client.ping()
    print "ping()\n"

    transport.close()

end