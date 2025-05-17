

## Mockito
```java
package com.example.controller;

import com.example.model.User;
import com.example.service.UserService;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.WebMvcTest;
import org.springframework.http.MediaType;
import org.springframework.test.web.servlet.MockMvc;

import java.util.Optional;

import static org.mockito.Mockito.*;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.*;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;
import static org.springframework.test.web.servlet.result.MockMvcResultHandlers.print;

@WebMvcTest(UserController.class)  // This annotation sets up the test for the UserController
class UserControllerTest {

    @Autowired
    private MockMvc mockMvc;

    @Mock
    private UserService userService;
    
	@MockBean 
	private UserService userService; // Mocking the service bean

    @InjectMocks
    private UserController userController;

    @BeforeEach
    void setUp() {
        MockitoAnnotations.openMocks(this);
    }

    @Test
    void testGetUserById_Success() throws Exception {
        // Arrange
        User mockUser = new User(1L, "John", "Doe", "john.doe@example.com");
        when(userService.findUserById(1L)).thenReturn(Optional.of(mockUser));

        // Act & Assert
        mockMvc.perform(get("/users/1"))
                .andDo(print())  // Print the request/response for debugging
                .andExpect(status().isOk())
                .andExpect(jsonPath("$.firstName").value("John"))
                .andExpect(jsonPath("$.lastName").value("Doe"));
    }

    @Test
    void testGetUserById_NotFound() throws Exception {
        // Arrange
        when(userService.findUserById(2L)).thenReturn(Optional.empty());

        // Act & Assert
        mockMvc.perform(get("/users/2"))
                .andDo(print())
                .andExpect(status().isNotFound());
    }

    @Test
    void testCreateUser() throws Exception {
        // Arrange
        User newUser = new User(null, "Jane", "Smith", "jane.smith@example.com");
        User savedUser = new User(1L, "Jane", "Smith", "jane.smith@example.com");
        when(userService.saveUser(newUser)).thenReturn(savedUser);

        // Act & Assert

```