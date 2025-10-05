# Example

This is an example provided with the `stern` library. It is implemented with the provided `http` library.

## Implementation

This example implements a basic stern server, with 2 `modules` and 2 `controllers`.
The [main_module](./include/main_module.h) holds:
- The [main_controller](./include/main_controller.h) that implements the heartbeat routes
- The [user_module](./include/user/user_module.h) that manages user-related features. It holds:
  - The [user_controller](./include/user/user_controller.h) that implements all user-related routes

### Available routes
The example implements a few routes:

|  Method  |   Path    | Parameters  | Description                              |
|:--------:|:---------:|:-----------:|------------------------------------------|
|  `GET`   |     /     |      -      | Heartbeat route, always returns 200 (OK) |
|  `GET`   |  /users/  |    Query    | Retrieves a user from its id             |
|  `POST`  |  /users/  |    Body     | Creates a new user                       |
|  `PUT`   |  /users/  | Query, Body | Updates a user's data from its id        |
| `DELETE` |  /users/  |    Query    | Deletes a user                           |

## How to run

After building the project (see [How to build](../README.md/#build)), you can run the example with the following command:
```shell
./example/example
```

The server will then start, and you will be able to make HTTP requests.

---
<center>

[HTTP](../lib/http/README.md) · [Network](../lib/network/README.md) · [Stern](../README.md)

</center>