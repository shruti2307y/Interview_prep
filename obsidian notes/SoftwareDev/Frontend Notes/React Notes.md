

### Redux toolkit with slic
```javascript
// userSlice.js
import { createSlice, createAsyncThunk } from '@reduxjs/toolkit';

// Thunk for asynchronous user login
export const loginUser = createAsyncThunk('user/login', async (credentials) => {
  // Simulate an API call
  const response = await fetch('/api/login', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(credentials),
  });
  return response.json(); // This will be the payload for fulfilled state
});

const userSlice = createSlice({
  name: 'user',
  initialState: { user: null, status: 'idle', error: null },
  reducers: {
    logout: (state) => {
      state.user = null;
      state.status = 'idle';
    },
  },
  extraReducers: (builder) => {
    builder
      .addCase(loginUser.pending, (state) => {
        state.status = 'loading';
      })
      .addCase(loginUser.fulfilled, (state, action) => {
        state.status = 'succeeded';
        state.user = action.payload;
      })
      .addCase(loginUser.rejected, (state, action) => {
        state.status = 'failed';
        state.error = action.error.message;
      });
  },
});

export const { logout } = userSlice.actions;
export default userSlice.reducer;

```

#### Store config
```javascript
// store.js
import { configureStore } from '@reduxjs/toolkit';
import counterReducer from './counterSlice';
import todoReducer from './todoSlice';
import userReducer from './userSlice';

const store = configureStore({
  reducer: {
    counter: counterReducer,
    todos: todoReducer,
    user: userReducer,
  },
});

export default store;

```

#### Using state
```javascript
// User.js
import React, { useState } from 'react';
import { useSelector, useDispatch } from 'react-redux';
import { loginUser, logout } from './userSlice';

const User = () => {
  const [username, setUsername] = useState('');
  const [password, setPassword] = useState('');
  const user = useSelector((state) => state.user.user);
  const status = useSelector((state) => state.user.status);
  const dispatch = useDispatch();

  const handleLogin = () => {
    dispatch(loginUser({ username, password }));
  };

  const handleLogout = () => {
    dispatch(logout());
  };

  return (
    <div>
      {user ? (
        <div>
          <h2>Welcome, {user.name}</h2>
          <button onClick={handleLogout}>Logout</button>
        </div>
      ) : (
        <div>
          <h2>Login</h2>
          <input
            type="text"
            value={username}
            onChange={(e) => setUsername(e.target.value)}
            placeholder="Username"
          />
          <input
            type="password"
            value={password}
            onChange={(e) => setPassword(e.target.value)}
            placeholder="Password"
          />
          <button onClick={handleLogin} disabled={status === 'loading'}>
            {status === 'loading' ? 'Logging in...' : 'Login'}
          </button>
        </div>
      )}
      {status === 'failed' && <p>Error logging in</p>}
    </div>
  );
};

export default User;

```


### Router
```javascript
// App.js
import React from 'react';
import { BrowserRouter as Router, Route, Switch, Link } from 'react-router-dom';
import Home from './Home';
import About from './About';
import Contact from './Contact';

const App = () => {
  return (
    <Router>
      <nav>
        <ul>
          <li><Link to="/">Home</Link></li>
          <li><Link to="/about">About</Link></li>
          <li><Link to="/contact">Contact</Link></li>
        </ul>
      </nav>

      <Switch>
        <Route exact path="/" component={Home} />
        <Route path="/about" component={About} />
        <Route path="/contact" component={Contact} />
      </Switch>
    </Router>
  );
};

export default App;

```

#### Navigating
```javascript
import React, { useState } from 'react';
import { Redirect } from 'react-router-dom';

const Login = () => {
  const [isLoggedIn, setIsLoggedIn] = useState(false);

  const handleLogin = () => {
    setIsLoggedIn(true); // Simulate login
  };

  if (isLoggedIn) {
    return <Redirect to="/dashboard" />;
  }

  return (
    <div>
      <h2>Please login</h2>
      <button onClick={handleLogin}>Login</button>
    </div>
  );
};

export default Login;





import React from 'react';
import { useHistory } from 'react-router-dom';

const Home = () => {
  const history = useHistory(); // Get access to the history object

  const goToAbout = () => {
    history.push('/about'); // Navigate to the /about route
  };

  return (
    <div>
      <h2>Home Page</h2>
      <button onClick={goToAbout}>Go to About Page</button>
    </div>
  );
};

export default Home;


import React from 'react';
import { useNavigate } from 'react-router-dom';

const Home = () => {
  const navigate = useNavigate(); // Get access to the navigate function

  const goToAbout = () => {
    navigate('/about'); // Navigate to the /about route
  };

  return (
    <div>
      <h2>Home Page</h2>
      <button onClick={goToAbout}>Go to About Page</button>
    </div>
  );
};

export default Home;

```

#### Using some props

```javascript

// Component A (where the redirect happens)
import React from 'react';
import { useHistory } from 'react-router-dom';

const ComponentA = () => {
  const history = useHistory();

  const handleRedirect = () => {
    history.push({
      pathname: '/component-b',
      state: { message: 'Hello from Component A' }
    });
  };

  return (
    <div>
      <h2>Component A</h2>
      <button onClick={handleRedirect}>Go to Component B</button>
    </div>
  );
};

export default ComponentA;
// Component B (receiving the props)
import React from 'react';
import { useLocation } from 'react-router-dom';

const ComponentB = () => {
  const location = useLocation(); // Get location object

  return (
    <div>
      <h2>Component B</h2>
      <p>{location.state?.message}</p> {/* Accessing the passed props */}
    </div>
  );
};

export default ComponentB;



```


### Lazy loading
```javascript
const LazyComponent = React.lazy(() => import('./LazyComponent'));

function App() {
  return (
    <Suspense fallback={<div>Loading...</div>}>
      <LazyComponent />
    </Suspense>
  );
}

import { BrowserRouter as Router, Route, Switch } from 'react-router-dom';
import React, { lazy, Suspense } from 'react';

const Home = lazy(() => import('./Home'));
const About = lazy(() => import('./About'));

const App = () => (
  <Router>
    <Suspense fallback={<div>Loading...</div>}>
      <Switch>
        <Route exact path="/" component={Home} />
        <Route path="/about" component={About} />
      </Switch>
    </Suspense>
  </Router>
);

```


#### Debouncing
```javascript
import { useCallback } from 'react';
import { debounce } from 'lodash';

const handleInputChange = useCallback(debounce((value) => {
  // Handle input change
}, 300), []);

```

### Calling Apis
### Example 1: Using `fetch`

The `fetch` API is a modern way to make network requests. It returns a Promise, which resolves to the `Response` object that represents the response to the request.

**GET Request with `fetch`**:
```javascript
// Example of a simple GET request using fetch
fetch('https://jsonplaceholder.typicode.com/posts/1')
  .then(response => {
    if (!response.ok) {
      throw new Error('Network response was not ok');
    }
    return response.json(); // Parse the JSON from the response
  })
  .then(data => {
    console.log(data); // Log the response data
  })
  .catch(error => {
    console.error('There was a problem with the fetch operation:', error);
  });
```

**POST Request with `fetch`**:
```javascript
// Example of a POST request using fetch
fetch('https://jsonplaceholder.typicode.com/posts', {
  method: 'POST', // Specify the request method
  headers: {
    'Content-Type': 'application/json' // Specify that the body is JSON
  },
  body: JSON.stringify({
    title: 'foo',
    body: 'bar',
    userId: 1
  })
})
  .then(response => {
    if (!response.ok) {
      throw new Error('Network response was not ok');
    }
    return response.json();
  })
  .then(data => {
    console.log('Post created:', data); // Log the new post data
  })
  .catch(error => {
    console.error('There was a problem with the fetch operation:', error);
  });
```

### Example 2: Using `axios`

`axios` is a popular HTTP client library for making network requests, which has some advantages over `fetch` such as automatic JSON parsing and easier error handling.

First, install axios if you haven’t:
```bash
npm install axios
```

**GET Request with `axios`**:
```javascript
import axios from 'axios';

// Example of a simple GET request using axios
axios.get('https://jsonplaceholder.typicode.com/posts/1')
  .then(response => {
    console.log(response.data); // The response is already parsed as JSON
  })
  .catch(error => {
    console.error('There was an error making the request:', error);
  });
```

**POST Request with `axios`**:
```javascript
import axios from 'axios';

// Example of a POST request using axios
axios.post('https://jsonplaceholder.typicode.com/posts', {
  title: 'foo',
  body: 'bar',
  userId: 1
})
  .then(response => {
    console.log('Post created:', response.data); // Log the new post data
  })
  .catch(error => {
    console.error('There was an error making the request:', error);
  });
```

### Differences between `fetch` and `axios`:

1. **Promise Handling**:
   - `fetch` only rejects a Promise on a network failure, while `axios` automatically throws an error for HTTP status codes like 404 or 500.
   - With `fetch`, you need to manually check `response.ok`.

2. **Data Parsing**:
   - `fetch` doesn’t automatically parse JSON, so you need to call `response.json()`.
   - `axios` automatically parses JSON, so you can directly access the response data via `response.data`.

3. **Interceptors**:
   - `axios` has built-in support for request and response interceptors, which can be useful for tasks like modifying headers or error handling before or after a request is made.

4. **Browser Support**:
   - `fetch` is a built-in API, while `axios` is a third-party library and needs to be installed. However, `axios` has better support for older browsers.