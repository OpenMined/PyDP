import pydp as pd

print("Successfully Imported pydp")

# print("Here are the available Status codes from the Base library")
# x = range(18)
# for n in x:
#     print(pd.StatusCode(n))

s = pd.Status(pd.StatusCode(3), "New status object")
print(s)

url = "http://test.com"
payload_content = "example payload content"

print("Setting payload: " + payload_content)
s.set_payload(url, payload_content)
print("Getting payload: ")
return_payload = s.get_payload(url)
print(return_payload)
print("Erasing payload")
s.erase_payload(url)
new_payload=s.get_payload(url)
print("New payload:")
print(new_payload)
