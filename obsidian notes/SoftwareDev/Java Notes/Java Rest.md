

## Rest Template

```java

@Configuration
public class RestTemplateConfig {

    @Bean
    public RestTemplate restTemplate(RestTemplateBuilder builder) {
        return builder
                .setConnectTimeout(Duration.ofSeconds(5))
                .setReadTimeout(Duration.ofSeconds(5))
                .build();
    }
}

@Service
public class ExternalApiService {

    @Autowired
    private RestTemplate restTemplate;

    public String fetchDataFromExternalApi(String userId, String authToken) {
        try {
            // Set the URL and query parameters
            String url = "https://api.example.com/data";

            // Add query parameters
            UriComponentsBuilder uriBuilder = UriComponentsBuilder.fromHttpUrl(url)
                    .queryParam("userId", userId)
                    .queryParam("active", "true");

            // Create headers
            HttpHeaders headers = new HttpHeaders();
            headers.set("Authorization", "Bearer " + authToken);  // Add Bearer token
            headers.setContentType(MediaType.APPLICATION_JSON);

            // Build the request entity
            HttpEntity<String> entity = new HttpEntity<>(headers);

            // Make the GET request and capture response
            ResponseEntity<String> response = restTemplate.exchange(
                    uriBuilder.toUriString(), 
                    HttpMethod.GET, 
                    entity, 
                    String.class
            );

            // Return response body
            return response.getBody();
        } catch (HttpClientErrorException e) {
            // Handle HTTP errors (e.g., 400, 404)
            return "Error fetching data: " + e.getMessage();
        }
    }
}

```


## WebClient

`WebClient` is part of Spring's reactive stack and is the preferred client for making non-blocking, asynchronous HTTP requests. It's highly customizable and more powerful for handling complex scenarios.

```java

@Configuration
public class WebClientConfig {

    @Bean
    public WebClient webClient(WebClient.Builder webClientBuilder) {
        return webClientBuilder
                .baseUrl("https://api.example.com")
                .build();
    }
}

@Service
public class ExternalApiService {

    @Autowired
    private WebClient webClient;

    public Mono<String> postDataToExternalApi(Map<String, String> requestData, String authToken) {
        return webClient.post()
                .uri("/submit")
                .header(HttpHeaders.AUTHORIZATION, "Bearer " + authToken)
                .contentType(MediaType.APPLICATION_JSON)
                .bodyValue(requestData)
                .retrieve()
                .bodyToMono(String.class)  // Process response as Mono<String>
                .onErrorResume(WebClientResponseException.class, ex -> {
                    // Handle HTTP error responses
                    return Mono.just("Error: " + ex.getMessage());
                });
    }
}


@Service
public class FileUploadService {

    @Autowired
    private WebClient webClient;

    public Mono<String> uploadFile(Resource fileResource, String fileName, Map<String, String> formData, String authToken) {
        MultipartBodyBuilder builder = new MultipartBodyBuilder();
        
        // Add form fields
        formData.forEach(builder::part);
        
        // Add file field
        builder.part("file", fileResource)
               .header(HttpHeaders.CONTENT_DISPOSITION, "form-data; name=\"file\"; filename=\"" + fileName + "\"");

        return webClient.post()
                .uri("/upload")
                .header(HttpHeaders.AUTHORIZATION, "Bearer " + authToken)
                .contentType(MediaType.MULTIPART_FORM_DATA)
                .bodyValue(builder.build())
                .retrieve()
                .bodyToMono(String.class)
                .onErrorResume(ex -> Mono.just("Upload failed: " + ex.getMessage()));
    }
}


```