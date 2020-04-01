import socket


HOST = '127.0.0.1'
PORT = 60003

def tcp_server():

    passwd = input("Password: ")

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))

        while True:
            s.listen()
            conn, addr = s.accept()
            print('Connected by', addr)
            msg_to_be_emailed = "Connected by " + str(addr[0]) + " " + str(addr[1])
            send_email("larsmayen94@hotmail.com", passwd, msg_to_be_emailed)
            while True:
                data = conn.recv(1024)
                if not data:
                    break
                print(data)


import smtplib, ssl

def send_email(receiver_email, passwd, msg_to_send):
    smtp_server = "smtp.gmail.com"
    port = 587  # For starttls
    sender_email = "picus.picus.canus@gmail.com"
    message =  "" + msg_to_send + ""


    # Create a secure SSL context
    context = ssl.create_default_context() #ssl.create_default_context(), I believe...

    # Try to log in to server and send email
    try:
        server = smtplib.SMTP(smtp_server,port)
        server.starttls(context=context) # Secure the connection
        server.login(sender_email, passwd)
        server.sendmail(sender_email, receiver_email, message)
    except Exception as e:
        # Print any error messages to stdout
        print(e)
    finally:
        server.quit() 



tcp_server()
